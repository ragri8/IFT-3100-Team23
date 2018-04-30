#include "RayCastCamera.h"


// fonction qui permet de calibrer la caméra en fonction la valeur courante de ses attributs
void RayCastCamera::calibrate()
{
	axis_z = orientation;
	axis_x = Vector(viewport_width * fov / viewport_height);
	axis_y = axis_x.cross(axis_z).normalize() * fov;
}
