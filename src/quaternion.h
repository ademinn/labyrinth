#pragma once
#include "vector.h"

class Quaternion
{
	Vector _v;
	double _w;


public:
	Quaternion(double x1 = 0, double y1 = 0, double z1 = 0, double w1 = 1);
	Quaternion(Vector const &v, double alfa);
	Quaternion(Quaternion const &);

	Quaternion &operator =(Quaternion const &);
	Quaternion &operator *=(Quaternion const &);
	friend Quaternion operator -(Quaternion const &);
	bool operator ==(Quaternion const &)const;
	
	Quaternion norm()const;
	void normalize();
	double x()const;
	double y()const;
	double z()const;
	double w()const;
	Vector getVector()const;
	double getAngle()const;
	bool isId()const;
};

Quaternion const Id(0, 0, 0, 1);

Quaternion operator *(Quaternion const &, Quaternion const &);
//void rotate(Vector &, Vector const &, double const);
bool operator !=(Quaternion const &, Quaternion const &);

double abs(Quaternion const &);