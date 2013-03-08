#include "labyrinth.h"
#include <cmath>

Labyrinth::Labyrinth(char level)
	: Object(labyrinth(10, level)), r(0.2), v(0, 0, 0), g0(0.0, 0.0, 20), curDir(0.0, 0.0, 1.0), z(0.0, 0.0, 1.0), tmpDir(0, 0, 1), dt(0.015), start(0, 0, 0), now(0, 0, 1), startM(I), nowM(I), graph(getGraph()), prev(0, 0, 1), flag(false), d(0, 0, 1)
{
	//pos = Vector(0.0, 0.0, 10.0 + r);
	GLfloat amb_color[] = {0.3f, 0.3f, 0.1f, 1};
    GLfloat dif_color[] = {0.5f, 0.5f, 0.1f, 1};
    GLfloat spec_color[] = {0.2f, 0.2f, 0.1f, 1};
	Material tmp(amb_color, dif_color, spec_color);
	_sphere = Object(sphere(r, 4, tmp));
	g = g0;
	for(size_t i = 0; i < _data.size(); ++i)
	{
		if(_data[i].matNum() == 2)
			pos = (10.0 + r) * _data[i].norm() / abs(_data[i].norm());
		if(_data[i].matNum() == 3)
			fin = (10.0 + r) * _data[i].norm() / abs(_data[i].norm());
	}
	nv = graph.size();
	for(size_t i = 0; i < nv; ++i)
	{
		graph[i].first *= 10.4 / abs(graph[i].first);
		graph[i].second *= 10.4 / abs(graph[i].second);
	}
	//std::cout << nv << '\n';
}

void Labyrinth::paintLab()
{
	if(!flag)
	{
		g = startM * (rotate(start, now) * g0);
		pos = pos + v * dt + g * dt * dt / 2;
		v = v + g * dt;
		int nmin;
		double min = 1000000;
		for(size_t i = 0; i < nv; ++i)
			if(dist(pos, graph[i].first) + dist(pos, graph[i].second) < min)
			{
				min = dist(pos, graph[i].first) + dist(pos, graph[i].second);
				nmin = i;
			}
		Vector v1 = graph[nmin].first - pos;
		Vector v2 = graph[nmin].second - pos;
		Vector x = multiply(multiply(v1, v2), v1 - v2);
		x = x / abs(x);
		x *= x * v1;
		if(fabs(abs(x - v2) + abs(v1 - x) - abs(v1 - v2)) > 2 * eps)
			if(abs(v1) < abs(v2))
				x = v1;
			else
				x = v2;
		if(abs(x) < 1.6 * r)
		{
			x = x / abs(x);
			pos = pos - 0.1 * x;
			x *= x * v;
			x = -x;
			Vector tmp = v + x;
			v = x + tmp;
			v *= 0.8;
		}
		pos = (10.0 + r) / abs(pos) * pos;
		if(abs(pos - fin) < 2 * r)
			flag = true;
		Vector tmp1 = pos / abs(pos);
		Vector tmp2 = multiply(v, tmp1);
		v = multiply(tmp1, tmp2);
		glMultMatrixd(rotate(start, now).get());
	}
	glMultMatrixd(startM.get());
	paint();
	glTranslated(pos.x(), pos.y(), pos.z());
	_sphere.paint();
}

void Labyrinth::setDir(Vector const &vect)
{
	startM = startM * rotate(start, now);
	nowM = I;
	start = vect;
	now = vect;
	prev = vect;
}

void Labyrinth::chDir(Vector const &vect)
{
	prev = now;
	now = vect;
}