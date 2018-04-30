#pragma once

#include "Vector.h"
#include "RayCastRay.h"
#include "SurfaceType.h"

class RayCastPlane
{

public:
	
	double radius;   // rayon de la sphère
	Vector position; // position du centre de la sphère
	Vector emission; // couleur émissive de la sphère
	Vector color;    // couleur diffuse de la sphère

	SurfaceType material; // type de réflexion de la sphère

							// constructeur
	RayCastPlane(double r, Vector p, Vector e, Vector c, SurfaceType m) : radius(r), position(p), emission(e), color(c), material(m) {}
	double intersect(const RayCastRay& ray) const;
	
};

