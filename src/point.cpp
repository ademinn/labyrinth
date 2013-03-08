#include "point.h"
#include <cmath>

Point::Point(double x, double y, double z)
{
	coord = new double[3];
	coord[0] = x;
	coord[1] = y;
	coord[2] = z;
}

Point::Point(double const *x)
{
	coord = new double[3];
	coord[0] = x[0];
	coord[1] = x[1];
	coord[2] = x[2];
}

Point::Point(Point const &p)
{
	coord = new double[3];
	coord[0] = p.coord[0];
	coord[1] = p.coord[1];
	coord[2] = p.coord[2];
}

Point::~Point()
{
	delete[] coord;
}

Point &Point::operator =(Point const &p)
{
	coord[0] = p.coord[0];
	coord[1] = p.coord[1];
	coord[2] = p.coord[2];
	return (*this);
}

bool Point::operator ==(Point const &p)const
{
	return ((fabs(coord[0] - p.coord[0]) < eps) && (fabs(coord[1] - p.coord[1]) < eps) && (fabs(coord[2] - p.coord[2]) < eps));
}

double Point::x()const
{
	return coord[0];
}

double Point::y()const
{
	return coord[1];
}

double Point::z()const
{
	return coord[2];
}

Point::operator const double *()const
{
	return coord;
}

bool operator !=(Point const &p1, Point const &p2)
{
	return (!(p1 == p2));
}

double dist(Point const &p1, Point const &p2)
{
	return (sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y()) + (p1.z() - p2.z()) * (p1.z() - p2.z())));
}