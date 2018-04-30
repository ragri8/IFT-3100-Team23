#pragma once

class Vector
{
public:

	double x, y, z;

	// construction
	Vector() : x(0.0), y(0.0), z(0.0) {}
	Vector(double x) : x(x), y(0.0), z(0.0) {}
	Vector(double x, double y) : x(x), y(y), z(0.0) {}
	Vector(double x, double y, double z) : x(x), y(y), z(z) {}

	double dot(const Vector& v) const;
	Vector cross(const Vector& v) const;
	Vector multiply(const Vector& v) const;
	Vector operator*(double s) const;
	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector& normalize();
};