// IFT3100H18 ~ blinn_phong_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommet
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorAmbient2;
uniform vec3 colorDiffuse;
uniform vec3 colorDiffuse2;
uniform vec3 colorSpecular;
uniform vec3 colorSpecular2;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position des sources de lumière
uniform vec3 lightPosition;
uniform vec3 lightPosition2;

void main()
{
  // re-normaliser la normale après interpolation
  vec3 N = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 L = normalize(lightPosition - viewSpacePosition);
  vec3 L2 = normalize(lightPosition2 - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);
  float reflectionDiffuse2 = max(dot(N, L2), 0.0);

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

  // calculer la couleur du fragment
  fragmentColor = vec4(
    colorAmbient + colorAmbient2 +
    colorDiffuse * reflectionDiffuse +
    colorDiffuse2 * reflectionDiffuse2 +
    colorSpecular * reflectionSpecular +
    colorSpecular2 * reflectionSpecular2, 1.0);
}
