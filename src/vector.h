#pragma once
#include "point.h"

class Vector : public Point
{
public:
	Vector(double x = 0.0, double y = 0.0, double z = 0.0);
	Vector(double const *);
	Vector(Vector const &);

	Vector &operator =(Vector const &);
	Vector &operator +=(Vector const &);
	Vector &operator -=(Vector const &);
	double operator *(Vector const &)const;
	Vector &operator *=(double const);
};

Vector operator +(Vector const &, Vector const &);
Vector operator -(Vector const &, Vector const &);
Vector operator -(Vector const &);
Vector operator *(Vector const &, double const);
Vector operator *(double const, Vector const &);
Vector &operator /=(Vector &, double const);
Vector operator /(Vector const &, double const);

double abs(Vector const &);
Vector multiply(Vector const &, Vector const &);
double angle(Vector const &, Vector const &);