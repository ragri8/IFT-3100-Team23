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
uniform vec3 lightColor2;
uniform vec3 lightColor3;

// couleur de la lumière ambiente
uniform vec3 lightAmbient;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// portée maximale d'une source de lumière
uniform float lightRange;

// position des sources de lumière
uniform vec3 lightPosition;
uniform vec3 lightPosition2;
uniform vec3 lightPosition3;

void main()
{
  // Prend en compte les distances modèle-lumière
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

  float D2 = distance(lightPosition2, viewSpacePosition);

  float distFactor2 = 1;
  distFactor2 = (lightRange - D2 + 10) / lightRange;
  if (distFactor2 > 1.0)
  {
    distFactor2 = 1.0;
  }
  else if (distFactor2 < 0.0)
  {
    distFactor2 = 0.0;
  }

  float D3 = distance(lightPosition3, viewSpacePosition);
  float distFactor3 = 1;
  distFactor3 = (lightRange - D3 + 10) / lightRange;
  if (distFactor3 > 1.0)
  {
    distFactor3 = 1.0;
  }
  else if (distFactor3 < 0.0)
  {
    distFactor3 = 0.0;
  }

  // re-normaliser la normale après interpolation
  vec3 N = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 L = normalize(lightPosition - viewSpacePosition);
  vec3 L2 = normalize(lightPosition2 - viewSpacePosition);
  vec3 L3 = normalize(lightPosition3 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);
  float reflectionDiffuse2 = max(dot(N, L2), 0.0);
  float reflectionDiffuse3 = max(dot(N, L3), 0.0);

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
  // réflexion spéculaire 2 par défaut
  float reflectionSpecular2 = 0.0;

  if (reflectionDiffuse2 > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction du demi-vecteur de réflection (H) en fonction du vecteur de vue (V) et de lumière (L)
    vec3 H = normalize(V + L2);

    // calculer le niveau de réflexion spéculaire (N • H)
    reflectionSpecular2 = pow(max(dot(N, H), 0.0), brightness) * 0.6;
  }
  // réflexion spéculaire 3 par défaut
  float reflectionSpecular3 = 0.0;

  if (reflectionDiffuse3 > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction du demi-vecteur de réflection (H) en fonction du vecteur de vue (V) et de lumière (L)
    vec3 H = normalize(V + L3);

    // calculer le niveau de réflexion spéculaire (N • H)
    reflectionSpecular3 = pow(max(dot(N, H), 0.0), brightness) * 0.6;
  }

  // calculer la couleur du fragment
  fragmentColor = vec4(
    colorAmbient * lightAmbient +
    colorDiffuse * (lightColor * reflectionDiffuse * distFactor +
    lightColor2 * reflectionDiffuse2 * distFactor2 +
    lightColor3 * reflectionDiffuse3 * distFactor3) +
    colorSpecular * (lightColor * reflectionSpecular * distFactor +
    lightColor2 * reflectionSpecular2 * distFactor2 +
    lightColor3 * reflectionSpecular3 * distFactor3), 1.0);
}
