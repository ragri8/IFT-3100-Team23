// IFT3100H18 ~ gouraud_330_fs.glsl

#version 330

// attribut interpolé à partir des valeurs en sortie du shader de sommet
in vec3 interpolationColor;

// attribut en sortie
out vec4 fragmentColor;

void main()
{
  // calculer la couleur du fragment
  fragmentColor = vec4(interpolationColor, 1.0);
}
