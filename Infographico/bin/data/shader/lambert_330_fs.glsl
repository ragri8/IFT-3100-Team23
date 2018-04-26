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

// position d'une source de lumière
uniform vec3 lightPosition;

void main()
{
  // re-normaliser la normale après interpolation (N)
  vec3 n = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 l = normalize(lightPosition - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflection_diffuse = max(dot(n, l), 0.0);

  // déterminer la couleur du fragment
  fragmentColor = vec4(colorAmbient + colorDiffuse * reflection_diffuse, 1.0);
}
