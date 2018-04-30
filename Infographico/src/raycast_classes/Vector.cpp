#include "Vector.h"

#include <math.h>   

// produit scalaire (dot product)
double Vector::dot(const Vector& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

// produit vectoriel (cross product)
Vector Vector::cross(const Vector& v) const
{
	return Vector(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

// multiplication vectorielle
Vector Vector::multiply(const Vector& v) const
{
	return Vector(
		x * v.x,
		y * v.y,
		z * v.z);
}

// multiplication scalaire
Vector Vector::operator*(double s) const
{
	return Vector(
		x * s,
		y * s,
		z * s);
}

// addition vectorielle
Vector Vector::operator+(const Vector& v) const
{
	return Vector(
		x + v.x,
		y + v.y,
		z + v.z);
}

// soustraction vectorielle
Vector Vector::operator-(const Vector& v) const
{
	return Vector(
		x - v.x,
		y - v.y,
		z - v.z);
}

// normalisation
Vector& Vector::normalize()
{
	return *this = *this * (1.0 / sqrt(x * x + y * y + z * z));
}