// IFT3100H18 ~ color_fill_330_fs.glsl

#version 330

// couleur de remplissage du matériau
uniform vec3 color;

// couleur de la lumière ambiente
uniform vec3 lightAmbient;

out vec4 fragmentColor;

void main()
{
  // déterminer la couleur du fragment
  fragmentColor = vec4(color * lightAmbient, 1.0);
}
