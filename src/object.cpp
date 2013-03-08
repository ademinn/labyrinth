#include "object.h"
#include <algorithm>

Object::Object(std::vector<Point> const &points, std::vector<Poly> const &poly, std::vector<Material> const &materials, std::vector<Vector> const &norm, std::vector<size_t> const &matNum)
	: _points(points), _materials(materials)
{
	for(size_t i = 0; i < poly.size(); ++i)
		_data.push_back(Data(poly[i], norm[i], matNum[i]));
	std::sort(_data.begin(), _data.end());
}

Object::Object(Object const &o)
	: _points(o._points), _data(o._data), _materials(o._materials)
{
}

Object::Object()
	: _data(), _points(), _materials()
{
}

Object const &Object::operator =(Object const &o)
{
	_data = o._data;
	_points = o._points;
	_materials = o._materials;
	return *this;
}

void Object::setData(std::vector<Point> const &points, std::vector<Poly> const &poly, std::vector<Material> const &materials, std::vector<Vector> const &norm, std::vector<size_t> const &matNum)
{
	_points = points;
	_materials = materials;
	_data.clear();
	for(size_t i = 0; i < poly.size(); ++i)
		_data.push_back(Data(poly[i], norm[i], matNum[i]));
	std::sort(_data.begin(), _data.end());
}

void Object::paint()
{
	//std::cout << _data.size() << '\n';
	if(_data.size() != 0)
	{
		_materials[_data[0].matNum()].setMaterial();
		glBegin(GL_POLYGON);
		for(size_t j = 0; j < _data[0].poly().size(); ++j)
		{
			glNormal3dv(_data[0].norm());
			glVertex3dv(_points[_data[0].poly()[j]]);
		}
		glEnd();
		for(size_t i = 1; i < _data.size(); ++i)
		{
			if(_data[i - 1].matNum() != _data[i].matNum())
				_materials[_data[i].matNum()].setMaterial();
			glBegin(GL_POLYGON);
			for(size_t j = 0; j < _data[i].poly().size(); ++j)
			{
				glNormal3dv(_data[i].norm());
				glVertex3dv(_points[_data[i].poly()[j]]);
			}
			glEnd();
		}
	}
}
/*Object::Object(std::vector<Point> const &points, std::vector<Poly> const &Polys, std::vector<Material> const &materials, std::vector<Vector> const &norm, std::vector<size_t> const &matNum)
	:_points(points), _Polys(Polys), _materials(materials), _norm(norm), _matNum(matNum)
{
}

Object::Object()
	:_points(), _norm(), _Polys(), _materials(), _matNum()
{
}

Object &Object::operator =(Object const &o)
{
	_points = o._points;
	_norm = o._norm;
	_Polys = o._Polys;
	_materials = o._materials;
	_matNum = o._matNum;
	return *this;
}

void Object::paint()
{
	for(size_t i = 0; i < _Polys.size(); ++i)
	{
		_materials[_matNum[i]].setMaterial();
		glBegin(GL_POLYGON);
	    for(size_t j = 0; j < _Polys[i].size(); ++j)
	    {
	        glNormal3dv(_norm[i]);
	        glVertex3dv(_points[_Polys[i][j]]);
	    }
	    glEnd();
	}
}

std::vector<Point> Object::points()const
{
	return _points;
}

std::vector<Poly> Object::Polys()const
{
	return _Polys;
}*/

///////////////////////////////////////////////////////////////////////////////////////

/*#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "object.h"
#include "vector.h"

size_t const inf = 1000000000;

Object::Object(std::string const &fileName)
{
    std::ifstream fin(fileName.c_str());
    size_t n, m;
    fin >> n;
    double x, y, z;
    for(size_t i = 0; i < n; ++i)
    {
        fin >> x >> y >> z;
        points.push_back(Point(x, y, z));
    }
    fin >> n;
    norm.resize(n);
    for(size_t i = 0; i < n; ++i)
    {
        fin >> m;
        if(m == inf)
        {
            start = i;
            fin >> m;
        }
        if(m == inf + 1)
        {
            finish = i;
            fin >> m;
        }
        std::vector<size_t> tmp;
        tmp.resize(m);
        for(size_t j = 0; j < m; ++j)
            fin >> tmp[j];
        Polys.push_back(tmp);
        setNorm(i);
    }
    std::cout << "OK";
}

void Object::setNorm(size_t k)
{
    Vector A(points[Polys[k][1]]);
    Vector B(points[Polys[k][0]]);
    Vector C(points[Polys[k][2]]);
    Vector v1 = B - A;
    Vector v2 = C - A;
    Vector n = multiply(v1, v2);
    if((n * A) < 0)
        n = -n;
    norm[k] = n;
}


void Object::cone(double radius, double height, size_t slices)
{

    Vector top(0, 0, height);
    double dAlpha = 2 * pi / slices;
    glBegin(GL_TRIANGLES);
    for(size_t i = 0; i < slices - 1; ++i)
    {
        Vector a(cos(dAlpha * i), sin(dAlpha * i), 0);
        a *= radius;
        Vector b(cos(dAlpha * (i + 1)), sin(dAlpha * (i + 1)), 0);
        b *= radius;
        Vector n = multiply((b - a), (top - a));
        glNormal3dv(n);
        glVertex3dv(top);
        glNormal3dv(n);
        glVertex3dv(a);
        glNormal3dv(n);
        glVertex3dv(b);
    }
    Vector a(cos(dAlpha * (slices - 1)), sin(dAlpha * (slices - 1)), 0);
    a *= radius;
    Vector b(cos(0.0), sin(0.0), 0);
    b *= radius;
    Vector n = multiply((b - a), (top - a));
    glNormal3dv(n);
    glVertex3dv(top);
    glNormal3dv(n);
    glVertex3dv(a);
    glNormal3dv(n);
    glVertex3dv(b);
    glEnd();
}

void Object::cone(double radius, size_t slices, Point const &p, Vector const &h)
{
    glPushMatrix();
    glTranslated(p.x(), p.y(), p.z());
    Vector v(0.0, 0.0, 1.0);
    Vector n = multiply(v, h);
    double ang = angle(v, h) * 180 / pi;
    glRotated(ang, n.x(), n.y(), n.z());
    cone(radius, abs(h), slices);
    glPopMatrix();
}

void Object::paint()
{
    GLfloat amb_color[] = {0.1f, 0.1f, 0.1f, 1};
    GLfloat dif_color[] = {0.1f, 0.1f, 0.1f, 1};
    GLfloat spec_color[] = {0.1f, 0.1f, 0.1f, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
	for(size_t i = 0; i < Polys.size(); ++i)
	{
	    if(Polys[i].size() == 4)
	    {
	        spec_color[0] = amb_color[0] = 0.4f;
	        spec_color[1] = amb_color[1] = 0.4f;
	        spec_color[2] = amb_color[2] = 0.4f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
	    }
	    if(i == start)
	    {
            spec_color[0] = amb_color[0] = 0;
	        spec_color[1] = amb_color[1] = 1;
	        spec_color[2] = amb_color[2] = 0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
	    }
	    if(i == finish)
	    {
	        spec_color[0] = amb_color[0] = 1;
	        spec_color[1] = amb_color[1] = 0;
	        spec_color[2] = amb_color[2] = 0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
	    }
	    glBegin(GL_POLYGON);
	    for(size_t j = 0; j < Polys[i].size(); ++j)
	    {
	        glNormal3dv(norm[i]);
	        glVertex3dv(points[Polys[i][j]]);
	    }
	    glEnd();
        if((i == start) || (i == finish))
        {

            spec_color[0] = amb_color[0] = 0.1f;
	        spec_color[1] = amb_color[1] = 0.1f;
	        spec_color[2] = amb_color[2] = 0.1f;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec_color);
        }
	}
/*	for(size_t i = 0; i < 162; ++i)
    {
        Vector h = Vector(points[i]) / abs(Vector(points[i])) / 2;
        cone(0.2, 10, points[i], h);
    }*/
//}