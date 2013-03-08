#pragma once
#include "primitives.h"
#include "matrix.h"
//#include <utility>

class Labyrinth : public Object
{
	Object _sphere;
	Vector pos;
	Vector pos0;
	Vector v;
	Vector g;
	Vector nullDir;
	Vector curDir;
	Vector tmpDir;
	Vector z;
	Vector g0;
	Vector start;
	Vector now;
	Vector prev;
	Vector fin;
	const double r;
	bool flag;
	//Quaternion nullPos, curPos;
	Matrix startM;
	Matrix nowM;
	double dt;
	Vector d;
	std::vector< std::pair<Vector, Vector> > graph;
	size_t nv;

public:
	Labyrinth(char level = 0);

	void paintLab();
	void setDir(Vector const &vect);
	void chDir(Vector const &vect);
};
