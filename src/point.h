#pragma once

#include <iostream>

class Point
{
protected:
	double *coord;

public:
	Point(double x = 0.0, double y = 0.0, double z = 0.0);
	Point(double const *);
	Point(Point const &);
	~Point();
	Point &operator =(Point const &);
	bool operator ==(Point const &)const;

	double x()const;
	double y()const;
	double z()const;

	operator double const *()const;
};

double const eps = 1e-15;
double const pi = 3.1415926536;

bool operator !=(Point const &, Point const &);
double dist(Point const &, Point const &);