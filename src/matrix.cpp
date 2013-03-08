#include "matrix.h"
#include <cmath>
Matrix::Matrix(std::vector< std::vector<double> > const &m)
	:_m(m)
{
	d = new double[16];
}

Matrix::Matrix()
{
	_m.resize(3);
	for(int i = 0; i < 3; ++i)
	{
		_m[i].resize(3);
		_m[i][i] = 1;
	}
	d = new double[16];
}

Matrix::Matrix(const Matrix &m)
	:_m(m._m)
{
	d = new double[16];
}

Matrix::Matrix(Vector const &v1, double ang)
{
	std::vector<double> tmp;
	double Cos = cos(ang), Sin = sin(ang);
	Vector v = v1 / abs(v1);
	tmp.push_back(Cos + (1 - Cos) * v.x() * v.x());
	tmp.push_back((1 - Cos) * v.x() * v.y() - Sin * v.z());
	tmp.push_back((1 - Cos) * v.x() * v.z() + Sin * v.y());
	_m.push_back(tmp);
	tmp[0] = (1 - Cos)* v.y() * v.x() + Sin * v.z();
	tmp[1] = Cos + (1 - Cos) * v.y() * v.y();
	tmp[2] = (1 - Cos) * v.y() * v.z() - Sin * v.x();
	_m.push_back(tmp);
	tmp[0] = (1 - Cos) * v.z() * v.x() - Sin * v.y();
	tmp[1] = (1 - Cos) * v.z() * v.y() + Sin * v.x();
	tmp[2] = Cos + (1 - Cos) * v.z() * v.z();
	_m.push_back(tmp);
	d = new double[16];
}

Matrix::~Matrix()
{
	delete[] d;
}

Matrix::Matrix(const Vector &v)
{
	_m.resize(3);
	for(int i = 0; i < 3; ++i)
		_m[i].resize(3);
	std::vector<double> tmp;
	tmp.resize(3);
	tmp[0] = v.x();
	tmp[1] = v.y();
	tmp[2] = v.z();
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			_m[i][j] = tmp[i] * tmp[j];
	d = new double[16];
}

Vector Matrix::operator *(Vector const &v)
{
	Vector tmp(
		_m[0][0] * v.x() + _m[0][1] * v.y() + _m[0][2] * v.z(),
		_m[1][0] * v.x() + _m[1][1] * v.y() + _m[1][2] * v.z(),
		_m[2][0] * v.x() + _m[2][1] * v.y() + _m[2][2] * v.z());
	return tmp;
}

Matrix &Matrix::operator *=(double const c)
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			_m[i][j] = c * _m[i][j];
	return *this;
}

Matrix &Matrix::operator +=(const Matrix &m)
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			_m[i][j] += m._m[i][j];
	return *this;
}

Matrix operator -(Matrix const &m)
{
	Matrix tmp(m);
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			tmp._m[i][j] = -tmp._m[i][j];
	return tmp;
}

Matrix &Matrix::operator =(Matrix const &m)
{
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			_m[i][j] = m._m[i][j];
	return *this;
}

Matrix operator +(Matrix const &m1, Matrix const &m2)
{
	Matrix tmp(m1);
	tmp += m2;
	return tmp;
}

Matrix operator -(Matrix const &m1, Matrix const &m2)
{
	return(m1 + (-m2));
}

Matrix operator *(double const c, Matrix const &m)
{
	Matrix tmp(m);
	tmp *= c;
	return tmp;
}

double *Matrix::get()const
{
	for(size_t i = 0; i < 3; ++i)
	{
		for(size_t j = 0; j < 3; ++j)
			d[4 * i + j] = _m[i][j];
		d[4 * (i + 1) - 1] = 0;
	}
	d[15] = 1;
	return d;
}

Matrix rotate(Vector const &v1, Vector const &v2)
{
	Vector n = multiply(v1, v2);
	if(abs(n) < eps)
		return I;
	double a = -angle(v1, v2);
	Vector u = n / abs(n);
	std::vector< std::vector<double> > s1;
	s1.resize(3);
	for(int i = 0; i < 3; ++i)
		s1[i].resize(3);
	s1[0][0] = 0;	s1[0][1] = -u.z();	s1[0][2] = u.y();
	s1[1][0] = u.z();	s1[1][1] = 0;		s1[1][2] = -u.x();
	s1[2][0] = -u.y();	s1[2][1] = u.x();	s1[2][2] = 0;
	Matrix S(s1);
	Matrix U(u);
	Matrix M = U + cos(a) * (I - U) + sin(a) * S;
	return M;
}

Matrix &Matrix::operator *=(Matrix const &m)
{
	Matrix tmp = *this;
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			_m[i][j] = 0;
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			for(int k = 0; k < 3; ++k)
				_m[i][j] += tmp._m[i][k] * m._m[k][j];
	return *this;
}

Matrix operator *(Matrix const &m1, Matrix const &m2)
{
	Matrix tmp(m1);
	tmp *= m2;
	return tmp;
}
