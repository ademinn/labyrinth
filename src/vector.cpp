#include "vector.h"
#include <math.h>
#include <cmath>

Vector::Vector(double x, double y, double z)
	: Point(x, y, z)
{
}

Vector::Vector(double const *x)
	: Point(x)
{
}

Vector::Vector(Vector const &v)
	: Point(v)
{
}

Vector &Vector::operator =(Vector const &v)
{
	coord[0] = v.coord[0];
	coord[1] = v.coord[1];
	coord[2] = v.coord[2];
	return (*this);
}

Vector &Vector::operator+=(Vector const &v)
{
	coord[0] += v.coord[0];
	coord[1] += v.coord[1];
	coord[2] += v.coord[2];
	return (*this);
}

Vector &Vector::operator-=(Vector const &v)
{
	coord[0] -= v.coord[0];
	coord[1] -= v.coord[1];
	coord[2] -= v.coord[2];
	return (*this);
}

double Vector::operator*(Vector const &v)const
{
	return(coord[0] * v.coord[0] + coord[1] * v.coord[1] + coord[2] * v.coord[2]);
}

Vector &Vector::operator *=(double const a)
{
	coord[0] *= a;
	coord[1] *= a;
	coord[2] *= a;
	return (*this);
}

Vector operator +(Vector const &v1, Vector const &v2)
{
	Vector tmp(v1);
	tmp += v2;
	return tmp;
}

Vector operator -(Vector const &v1, Vector const &v2)
{
	Vector tmp(v1);
	tmp -= v2;
	return tmp;
}

Vector operator -(Vector const &v)
{
	Vector tmp(0, 0, 0);
	tmp -= v;
	return tmp;
}

Vector operator *(Vector const &v, double const a)
{
	Vector tmp(v);
	tmp *= a;
	return tmp;
}

Vector operator *(double const a, Vector const &v)
{
	Vector tmp(v);
	tmp *= a;
	return tmp;
}
Vector &operator /=(Vector &v, double const d)
{
	v *= (1 / d);
	return v;
}

Vector operator /(Vector const &v1, double const d)
{
	Vector tmp(v1);
	tmp /= d;
	return tmp;
}

double abs(Vector const &v)
{
	return sqrt(v.x() * v.x() + v.y() * v.y() + v.z() * v.z());
}

Vector multiply(Vector const & v1, Vector const &v2)
{
	Vector tmp(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
	return (tmp);
}

double angle(Vector const &v1, Vector const &v2)
{
	return acos((v1 * v2) / (abs(v1) * abs(v2)));
}