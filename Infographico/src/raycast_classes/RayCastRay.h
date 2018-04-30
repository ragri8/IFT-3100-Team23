#pragma once

#include "Vector.h"

class RayCastRay
{	

public:
	Vector origin;
	Vector direction;

	RayCastRay(Vector o, Vector d) : origin(o), direction(d) {}
};
