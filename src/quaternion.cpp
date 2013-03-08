#include "quaternion.h"
#include <math.h>
#include <vector>
#include "matrix.h"

Quaternion::Quaternion(double x1, double y1, double z1, double w1)
	: _v(x1, y1, z1), _w(w1)
{
}

Quaternion::Quaternion(Vector const &v, double alpha)
	: _v(v.x() * sin(alpha / 2), v.y() * sin(alpha / 2), v.z() * sin(alpha / 2)), _w(cos(alpha / 2))
{
}

Quaternion::Quaternion(Quaternion const &q)
	: _v(q._v), _w(q._w)
{
}

Quaternion &Quaternion::operator =(Quaternion const &q)
{
	_v = q._v;
	_w = q._w;
	return (*this);
}

Quaternion &Quaternion::operator *=(Quaternion const &q)
{
	Vector v(_v);
	Vector v1(q._v);
	Vector v2 = multiply(v, v1) + _w * v1 + q._w * v;
	_w = _w * q._w - v * v1;
	_v = v2;
	return (*this);
}

Quaternion operator *(Quaternion const &q1, Quaternion const &q2)
{
	Quaternion tmp(q1);
	tmp *= q2;
	return tmp;
}

bool Quaternion::isId()const
{
	return(fabs(_v.x()) < eps && fabs(_v.y()) < eps && fabs(_v.z()) < eps);
}

double Quaternion::x()const
{
	return _v.x();
}

double Quaternion::y()const
{
	return _v.y();
}

double Quaternion::z()const
{
	return _v.z();
}

double Quaternion::w()const
{
	return _w;
}

double abs(Quaternion const &q)
{
	return (sqrt(q.x() * q.x() + q.y() * q.y() + q.z() * q.z() + q.w() * q.w()));
}

Quaternion Quaternion::norm()const
{
	Quaternion tmp(*this);
	tmp.normalize();
	return tmp;
}

void Quaternion::normalize()
{
	double tmp = abs(*this);
	_v *= (1.0 / tmp);
	_w /= tmp;
}

bool Quaternion::operator ==(Quaternion const &q)const
{
	return ((_v == q._v) && ((_w - q._w) < eps));
}

bool operator !=(Quaternion const &q1, Quaternion const &q2)
{
	return (!(q1 == q2));
}

double Quaternion::getAngle()const
{
	return (*this == Id ? 0 : acos(_w) * 2 * 180 / pi);
}

Vector Quaternion::getVector()const
{
	return (*this == Id ? _v : _v * (1.0 / sin(acos(_w))));
}
/*
void rotate(Vector &vect, Vector const &n, double const a)
{
	//if(!q.isId() && fabs(q.getAngle()) >= eps)
		Vector v = n;
		Vector u = v / abs(v);
		//std::cout << v.x() << " " << v.y() << " " << v.z() << '\n';
		//double a = q.getAngle() * pi / 180;
		//std::cout << a << '\n';
		std::vector<std::vector<double>> s1;
		s1.resize(3);
		for(int i = 0; i < 3; ++i)
			s1[i].resize(3);
		s1[0][0] = 0;	s1[0][1] = -u.z();	s1[0][2] = u.y();
		s1[1][0] = u.z();	s1[1][1] = 0;		s1[1][2] = -u.x();
		s1[2][0] = -u.y();	s1[2][1] = u.x();	s1[2][2] = 0;
		Matrix S(s1);
		Matrix U(u);
		Matrix M = U + cos(a) * (I - U) + sin(a) * S;
		vect = M * vect;
		/*for(int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; ++j)
				std::cout << M._m[i][j] << " ";
			std::cout << '\n';
		}
		std::cout << '\n';
		//vect = 10.4 * vect / abs(vect);
		//std::cout << abs(vect) << '\n';
		std::cout << vect.x() << " " << vect.y() << " " << vect.z() << '\n';
		/*Vector n = q.getVector();
		n /= abs(n);
		Vector v1 = multiply(n, v);
		double ang = q.getAngle() * pi / 180;
		v = v * cos(ang) + v1 * sin(ang);*/
//}

Quaternion operator -(Quaternion const &q)
{
	Quaternion tmp(q);
	tmp._w = -tmp._w;
	return tmp;
}