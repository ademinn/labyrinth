#pragma once
#include <vector>
#include "material.h"
#include "point.h"
//#include "vector.h"
//#include "poly.h"
#include "data.h"

class Object
{
protected:
	std::vector<Data> _data;
	std::vector<Point> _points;
	//std::vector<Poly> _Polys;
	std::vector<Material> _materials;
	//std::vector<Vector> _norm;
	//std::vector<size_t> _matNum;

public:
	Object(std::vector<Point> const &points, std::vector<Poly> const &poly, std::vector<Material> const &materials, std::vector<Vector> const &norm, std::vector<size_t> const &matNum);
	Object(Object const &o);
	Object();
	Object const &operator =(Object const &);
	void paint();

	void setData(std::vector<Point> const &points, std::vector<Poly> const &poly, std::vector<Material> const &materials, std::vector<Vector> const &norm, std::vector<size_t> const &matNum);
	//std::vector<Point> points()const;
	//std::vector<Poly> Polys()const;
};
/*#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <string>
#include <vector>
#include "Poly.h"
#include "point.h"
#include "vector.h"

class Object
{
	std::vector<Poly> Polys;
	std::vector<Point> points;
	std::vector<Vector> norm;
	void setNorm(size_t);
	size_t start, finish;
	void cone(double radius, double height, size_t slices);
	void cone(double radius, size_t slices, Point const &p, Vector const &h);

public:
	Object(std::string const &);
	void paint();
};*/

//Object icosahedron("icosahedron");