#include "primitives.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

namespace
{
	std::vector<Point> points;
	std::vector<Poly> poly;
	std::vector<Material> materials;
	std::vector<Vector> norm;
	std::vector<size_t> matNum;
	Object answer;
	size_t m, start, fin;
	std::vector< std::vector<size_t> > sphGraph;
	std::vector< std::vector<size_t> > way;
	std::vector<bool> isEmpty;
	bool flag;
	double length;
	std::vector< std::pair<Vector, Vector> > graph;
	size_t nv;
}

void clear()
{
	points.clear();
	poly.clear();
	materials.clear();
	norm.clear();
	matNum.clear();
	start = 0;
	fin = 0;
	length = 0;
	m = 0;
	sphGraph.clear();
	way.clear();
	isEmpty.clear();
	flag = false;
}

void genCone(Point const &point, Vector const &h, double radius, size_t slices, size_t material)
{
	size_t n = points.size();
	Vector tmp = Vector(point);
	points.push_back(h + tmp);
	double x, y, z;
	if(fabs(h.x()) < eps)
	{
		x = 1;
		y = 0;
		z = 0;
	}else
	{
		y = 10;
		z = 10;
		x = -(h.y() * y + h.z() * z) / h.x();
	}
	Vector r(x, y, z);
	r *= radius / abs(r);
	points.push_back(r + tmp);
	Vector r1 = r;
	Vector r2;
	Matrix m;
	double ang = 2 * pi / slices;
	for(size_t i = 0; i < slices - 1; ++i)
	{
		m = Matrix(h, 2 * pi * (i + 1) / slices);
		r2 = m * r;
		points.push_back(r2 + tmp);
		poly.push_back(Poly(n, points.size() - 1, points.size() - 2));
		norm.push_back(-multiply(r2 - h, r1 - h));
		matNum.push_back(material);
		r1 = r2;
	}
	poly.push_back(Poly(n, n + 1, points.size() - 1));
	norm.push_back(-multiply(r - h, r2 - h));
	matNum.push_back(material);
}

Object const &cone(Point const &point, Vector const &h, double radius, size_t slices, Material const &material)
{
	clear();
	genCone(point, h, radius, slices, 0);
	materials.push_back(material);
	answer = Object(points, poly, materials, norm, matNum);
	return answer;
}

Object const &icosahedron(double radius, Material const &material)
{
	clear();
	double phi = (1 + sqrt(5.0)) / 2;
	double d = radius / sqrt(1 + phi * phi);
	phi *= d;
	points.push_back(Point(0, d, phi));
	points.push_back(Point(0, -d, phi));
	points.push_back(Point(0, d, -phi));
	points.push_back(Point(0, -d, -phi));
	points.push_back(Point(d, phi, 0));
	points.push_back(Point(-d, phi, 0));
	points.push_back(Point(d, -phi, 0));
	points.push_back(Point(-d, -phi, 0));
	points.push_back(Point(phi, 0, d));
	points.push_back(Point(phi, 0, -d));
	points.push_back(Point(-phi, 0, d));
	points.push_back(Point(-phi, 0, -d));
	poly.push_back(Poly(0, 1, 10));
	poly.push_back(Poly(0, 8, 1));
	poly.push_back(Poly(0, 4, 8));
	poly.push_back(Poly(0, 5, 4));
	poly.push_back(Poly(0, 10, 5));
	poly.push_back(Poly(7, 1, 6));
	poly.push_back(Poly(7, 10, 1));
	poly.push_back(Poly(7, 11, 10));
	poly.push_back(Poly(7, 3, 11));
	poly.push_back(Poly(7, 6, 3));
	poly.push_back(Poly(9, 8, 4));
	poly.push_back(Poly(9, 6, 8));
	poly.push_back(Poly(9, 3, 6));
	poly.push_back(Poly(9, 2, 3));
	poly.push_back(Poly(9, 4, 2));
	poly.push_back(Poly(8, 6, 1));
	poly.push_back(Poly(2, 11, 3));
	poly.push_back(Poly(2, 5, 11));
	poly.push_back(Poly(5, 10, 11));
	poly.push_back(Poly(2, 4, 5));
	for(size_t i = 0; i < 20; ++i)
	{
		norm.push_back(multiply(Vector(points[poly[i][2]]) - Vector(points[poly[i][1]]),Vector(points[poly[i][0]]) - Vector(points[poly[i][1]])));
		matNum.push_back(0);
	}
	materials.push_back(material);
	answer.setData(points, poly, materials, norm, matNum);
	return answer;
}

size_t middle(size_t v1, size_t v2)
{
	for(size_t i = 0; i < sphGraph[v1].size(); ++i)
		if(sphGraph[v1][i] == v2)
			return way[v1][i];
	return inf;
}

size_t newVertex(size_t v1, size_t v2)
{
	if(middle(v1, v2) == inf)
	{
		if(std::max(v1, v2) >= sphGraph.size())
		{
			sphGraph.resize(std::max(v1, v2) + 1);
			way.resize(std::max(v1, v2) + 1);
		}
		size_t v = points.size();
		Vector vect = Vector(points[v1]) + Vector(points[v2]);
		vect *= abs(Vector(points[v1])) / abs(vect);
		points.push_back(vect);
		sphGraph[v1].push_back(v2);
		way[v1].push_back(v);
		sphGraph[v2].push_back(v1);
		way[v2].push_back(v);
		return v;
	} else
		return middle(v1, v2);
}

void genSphere(size_t v1, size_t v2, size_t v3, char depth)
{
	if(depth == m)
		poly.push_back(Poly(v1, v2, v3));
	else
	{
		size_t v4 = newVertex(v1, v2);
		size_t v5 = newVertex(v2, v3);
		size_t v6 = newVertex(v3, v1);
		++depth;
		genSphere(v1, v4, v6, depth);
		genSphere(v4, v2, v5, depth);
		genSphere(v6, v5, v3, depth);
		genSphere(v4, v5, v6, depth);
	}
}

Object const &sphere(double radius, char k, Material const &material)
{
	icosahedron(radius);
	sphGraph.resize(12);
	way.resize(12);
	m = k;
	std::vector<Poly> tmp = poly;
	poly.clear();
	for(size_t i = 0; i < tmp.size(); ++i)
		genSphere(tmp[i][0], tmp[i][1], tmp[i][2], 0);
	norm.clear();
	materials.clear();
	matNum.clear();
	for(size_t i = 0; i < poly.size(); ++i)
	{
		norm.push_back(multiply(Vector(points[poly[i][0]]) - Vector(points[poly[i][1]]), Vector(points[poly[i][2]]) - Vector(points[poly[i][1]])));
		matNum.push_back(0);
	}
	materials.push_back(material);
	length = abs(Vector(points[poly[0][0]]) - Vector(points[poly[0][1]]));
	sphGraph.clear();
	way.clear();
	answer.setData(points, poly, materials, norm, matNum);
	return answer;
}

void generateWalls(size_t n, size_t depth)
{
	isEmpty[n] = false;
	if((depth == poly.size() / 3) && (!flag))
	{
		start = n;
		flag = true;
		return;
	}
	if(depth == poly.size() / 4)
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
					Edge e = compare(poly[i], poly[sphGraph[i][j]]);
					//graph[e.A()][e.B()] = true;
					//graph[e.B()][e.A()] = true;
					graph.push_back(std::make_pair(Vector(points[e.A()]), Vector(points[e.B()])));
					size_t C, D, A1, B1, A2, B2;
					if(pointFlag[e.A()] == inf)
					{
						pointFlag[e.A()] = points.size();
						D = points.size();
						points.push_back(Point(Vector(points[e.A()]) * (abs(Vector(points[e.A()])) + length / 3) / abs(Vector(points[e.A()]))));
					}else
						D = pointFlag[e.A()];
					if(pointFlag[e.B()] == inf)
					{
						pointFlag[e.B()] = points.size();
						C = points.size();
						points.push_back(Point(Vector(points[e.B()]) * (abs(Vector(points[e.B()])) + length / 3) / abs(Vector(points[e.B()]))));
					}else
						C = pointFlag[e.B()];
                    Vector n = multiply(Vector(points[e.A()]) - Vector(points[C]), Vector(points[C]) - Vector(points[D]));
                    n *= length / 10 / abs(n);
                    A1 = points.size();
                    points.push_back(Point(Vector(points[e.A()]) + n));
                    B1 = points.size();
                    points.push_back(Point(Vector(points[e.B()]) + n));
                    A2 = points.size();
                    points.push_back(Point(Vector(points[e.A()]) - n));
                    B2 = points.size();
                    points.push_back(Point(Vector(points[e.B()]) - n));
					poly.push_back(Poly(A1, B1, C, D));
					matNum.push_back(1);
					n = multiply(Vector(points[A1]) - Vector(points[B1]), Vector(points[C]) - Vector(points[B1]));
					if(n * Vector(points[B1]) < 0)
						n = -n;
					norm.push_back(n);
					poly.push_back(Poly(A2, B2, C, D));
					matNum.push_back(1);
					n = multiply(Vector(points[A2]) - Vector(points[B2]), Vector(points[C]) - Vector(points[B2]));
					if(n * Vector(points[B2]) < 0)
						n = -n;
					norm.push_back(n);
				}
			}
}

/*void tmp(Material const &floor)
{
	freopen("sphere5", "r", stdin);
	int n;
	scanf("%d", &n);
	float x, y, z;
	std::cout << n;
	for(int i = 0; i < n; ++i)
	{
		scanf("%f %f %f", &x, &y, &z);
		points.push_back(Point(x, y, z));
		//std::cout << x << " " << y << " " << z << '\n';
	}
	scanf("%d", &n);
	materials.push_back(floor);
	size_t a, b, c;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %f %f %f", &a, &b, &c, &x, &y, &z);
		poly.push_back(Poly(a, b, c));
		norm.push_back(Vector(x, y, z));
		matNum.push_back(0);
	}
	scanf("%d", &n);
	std::cout << n;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d %d %d %f %f %f", &a, &b, &c, &x, &y, &z);
		poly.push_back(Poly(a, b, c));
		norm.push_back(Vector(x, y, z));
		matNum.push_back(0);
	}
	std::cout << points.size() << " " << poly.size() << " " << materials.size();
	
}*/

Object const &labyrinth(double radius, char level, Material const &floor, Material const &walls)
{
	srand(static_cast<unsigned int>(time(NULL)));
	sphere(radius, level, floor);
	/*char c = '0' + k;
	std::string name = "sphere";
	name += c;
	std::cout << name;
	freopen(name.c_str(), "w", stdout);*/
	size_t n = points.size();
	//graph.resize(n);
	//for(int i = 0; i < n; ++i)
		//graph[i].resize(n);
	//nv = n;
	way.resize(poly.size());
	isEmpty.resize(poly.size());
	isEmpty.assign(poly.size(), true);
	sphGraph.resize(poly.size());
	for(size_t i = 0; i < poly.size() - 1; ++i)
		for(size_t j = i + 1; j < poly.size(); ++j)
			if(compare(poly[i], poly[j]) != NullEdge)
			{
				sphGraph[i].push_back(j);
				sphGraph[j].push_back(i);
			}
	fin = rand() % poly.size();
	generateWalls(fin, 0);
	makeAns();
	materials.push_back(walls);
	size_t m = poly.size();
	for(size_t i = 0; i < n; ++i)
		genCone(points[i], Vector(points[i]) * length / 3 / abs(Vector(points[i])), length / 10, 20, materials.size() - 1);
	GLfloat ambient[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat diffuse[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat specular[] = {0.0f, 1.0f, 1.0f, 1.0f};
	Material startM(ambient, diffuse, specular);
	ambient[0] = 1.0f;
	diffuse[0] = 1.0f;
	specular[0] = 1.0f;
	ambient[1] = 0.0f;
	diffuse[1] = 0.0f;
	specular[1] = 0.0f;
	Material finM(ambient, diffuse, specular);
	materials.push_back(startM);
	materials.push_back(finM);
	matNum[start] = 2;
	matNum[fin] = 3;
	answer.setData(points, poly, materials, norm, matNum);
	//std::cout << poly.size() << " -> ";
	return answer;
	/*printf("%d\n", points.size());
	for(size_t i = 0; i < points.size(); ++i)
		printf("%f %f %f\n", points[i].x(), points[i].y(), points[i].z());
	printf("%d\n", m);
	for(size_t i = 0; i < m; ++i)
		printf("%d %d %d %f %f %f\n", Polys[i][0], Polys[i][1], Polys[i][2], norm[i].x(), norm[i].y(), norm[i].z());
	printf("%d\n", Polys.size() - m);
	for(size_t i = m; i < Polys.size(); ++i)
				printf("%d %d %d %f %f %f\n", Polys[i][0], Polys[i][1], Polys[i][2], norm[i].x(), norm[i].y(), norm[i].z());
	answer = Object(points, Polys, materials, norm, matNum);
	return answer;
	tmp(floor);
	answer = Object(points, Polys, materials, norm, matNum);
	return answer;*/
}

std::vector< std::pair<Vector, Vector> > const &getGraph()
{
	return graph;
}
