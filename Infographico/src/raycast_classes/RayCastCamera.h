#pragma once

#include "Vector.h"

class RayCastCamera
{
public:
	Vector position;
	Vector orientation;
	Vector target;

	Vector axis_x;
	Vector axis_y;
	Vector axis_z;

	Vector up;

	float viewport_width;
	float viewport_height;

	float fov;

	RayCastCamera(Vector p, Vector o) : position(p), orientation(o) {}

	void calibrate();
};

