#include "generator.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "face.h"
#include "point.h"
#include "vector.h"

std::vector< std::vector<size_t> > sphGraph;
std::vector< std::vector<size_t> > way;
std::vector<Point> points;
std::vector<Face> faces;
std::vector<bool> isEmpty;

size_t start, fin;
bool flag;

static void readData(std::string);

static void generateWalls(size_t, size_t);

static void makeAns();

static void printAns(std::string);

void generate()
{
	srand(static_cast<unsigned int>(time(NULL)));
	readData("sphere.ASE");
	fin = rand() % faces.size();
	generateWalls(fin, 0);
	makeAns();
	printAns("sphere");
}

void readData(std::string s)
{
	std::ifstream fin(s.c_str());
	double x, y, z;
	int a, b, c;
	while(fin >> s)
	{
		if(s == "*MESH_NUMFACES")
		{
			fin >> a;
			sphGraph.resize(a);
			way.resize(a);
			isEmpty.assign(a, true);
		}
		else if(s == "*MESH_VERTEX")
		{
			fin >> a >> x >> y >> z;
			points.push_back(Point(x, y, z));
		}
		else if(s == "*MESH_FACE")
		{
			fin >> s >> s >> a >> s >> b >> s >> c;
			Face tmp(a, b, c);
			for(size_t i = 0; i < faces.size(); ++i)
				if(compare(tmp, faces[i]) != NullEdge)
				{
					sphGraph[i].push_back(faces.size());
					sphGraph[faces.size()].push_back(i);
				}
			faces.push_back(tmp);
		}
	}
}

void generateWalls(size_t n, size_t depth)
{
	isEmpty[n] = false;
	if((depth == 70) && (!flag))
	{
		start = n;
		flag = true;
		return;
	}
	if(depth == 60)
		return;
	size_t k = 1;
	while(k != 0)
	{
		std::vector<size_t> tmp;
		for(size_t i = 0; i < sphGraph[n].size(); ++i)
			if(isEmpty[sphGraph[n][i]])
				tmp.push_back(sphGraph[n][i]);
		k = tmp.size();
		if(k != 0)
		{
			size_t rnd = rand() % k;
			way[n].push_back(tmp[rnd]);
			way[tmp[rnd]].push_back(n);
			generateWalls(tmp[rnd], depth + 1);
		}
	}
}

void makeAns()
{
	std::vector<size_t> pointFlag;
	pointFlag.assign(points.size(), inf);
	bool b;
	for(size_t i = 0; i < sphGraph.size(); ++i)
		for(size_t j = 0; j < sphGraph[i].size(); ++j)
			if(sphGraph[i][j] > i)
			{
				b = true;
				for(size_t k = 0; k < way[i].size(); ++k)
					if(sphGraph[i][j] == way[i][k])
					{
						b = false;
						break;
					}
				if(b)
				{
					Edge e = compare(faces[i], faces[sphGraph[i][j]]);
					size_t C, D, A1, B1, A2, B2;
					if(pointFlag[e.A()] == inf)
					{
						pointFlag[e.A()] = points.size();
						D = points.size();
						points.push_back(Point(Vector(points[e.A()]) * (11.0 / 10)));
					}else
						D = pointFlag[e.A()];
					if(pointFlag[e.B()] == inf)
					{
						pointFlag[e.B()] = points.size();
						C = points.size();
						points.push_back(Point(Vector(points[e.B()]) * (11.0 / 10)));
					}else
						C = pointFlag[e.B()];
                    Vector n = multiply(Vector(points[e.A()]) - Vector(points[C]), Vector(points[C]) - Vector(points[D]));
                    n /= 5 * abs(n);
                    A1 = points.size();
                    points.push_back(Point(Vector(points[e.A()]) + n));
                    B1 = points.size();
                    points.push_back(Point(Vector(points[e.B()]) + n));
                    A2 = points.size();
                    points.push_back(Point(Vector(points[e.A()]) - n));
                    B2 = points.size();
                    points.push_back(Point(Vector(points[e.B()]) - n));
					faces.push_back(Face(A1, B1, C, D));
					faces.push_back(Face(A2, B2, C, D));
				}
			}
}

void printAns(std::string s)
{
	std::ofstream fout(s.c_str());
	fout << points.size() << '\n';
	for(size_t i = 0; i < points.size(); ++i)
		fout << points[i].x() << ' ' << points[i].y() << ' ' << points[i].z() << '\n';
	fout << faces.size() << '\n';
	for(size_t i = 0; i < faces.size(); ++i)
	{
	    if(i == start)
            fout << inf << ' ';
        if(i == fin)
            fout << inf + 1 << ' ';
	    fout << faces[i].size();
		for(size_t j = 0; j < faces[i].size(); ++j)
			fout << ' ' << faces[i][j];
		fout << '\n';
	}
}
