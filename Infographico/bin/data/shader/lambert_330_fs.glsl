// IFT3100H18 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 viewSpacePosition;
in vec3 viewSpaceNormal;

// attribut en sortie
out vec4 fragmentColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;

// portée maximale d'une source de lumière
uniform float lightRange;

// opacité de la brume, nombre de teinte par pixel parcouru
uniform float fogOpacity;

// couleur de la lumière
uniform vec3 lightColor;

// couleur de la lumière ambiente
uniform vec3 lightAmbient;

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

  // composante de brume en fonction de la distance et de son opacité
  float fogValue = length(viewSpacePosition) * fogOpacity / 255;
  vec3 fog = vec3(fogValue, fogValue, fogValue);
  
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor = vec4(colorAmbient * lightAmbient + colorDiffuse * reflection_diffuse * lightColor * distFactor + fog, 1.0);
}
