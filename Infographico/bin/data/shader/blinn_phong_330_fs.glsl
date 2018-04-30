// IFT3100H18 ~ blinn_phong_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;

// couleur de la lumière
uniform vec3 lightColor;

// couleur de la lumière ambiente
uniform vec3 lightAmbient;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// portée maximale d'une source de lumière
uniform float lightRange;

// position d'une source de lumière
uniform vec3 lightPosition;

void main()
{
  // Prend en compte la distance modèle-lumière
  float D = distance(lightPosition, viewSpacePosition);

  float distFactor = 1;
  distFactor = (lightRange - D + 10) / lightRange;
  if (distFactor > 1.0)
  {
    distFactor = 1.0;
  }
  else if (distFactor < 0.0)
  {
    distFactor = 0.0;
  }
  
  // re-normaliser la normale après interpolation
  vec3 N = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 L = normalize(lightPosition - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction du demi-vecteur de réflection (H) en fonction du vecteur de vue (V) et de lumière (L)
    vec3 H = normalize(V + L);

    // calculer le niveau de réflexion spéculaire (N • H)
    reflectionSpecular = pow(max(dot(N, H), 0.0), brightness);
  }

  // calculer la couleur du fragment
  fragmentColor = vec4(
    colorAmbient * lightAmbient +
    colorDiffuse * reflectionDiffuse * lightColor * distFactor +
    colorSpecular * reflectionSpecular * lightColor * distFactor, 1.0);
}
