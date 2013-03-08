#include "data.h"

Data::Data(Poly const &poly, Vector const &norm, size_t matNum)
	: _poly(poly), _norm(norm), _matNum(matNum)
{
}

Data::Data(Data const &d)
	: _poly(d._poly), _norm(d._norm), _matNum(d._matNum)
{
}

Data::Data()
	: _poly(), _norm(), _matNum()
{
}

Data const &Data::operator =(Data const &d)
{
	_poly = d._poly;
	_norm = d._norm;
	_matNum = d._matNum;
	return *this;
}

Poly const &Data::poly() const
{
	return _poly;
}

Vector const &Data::norm() const
{
	return _norm;
}

size_t Data::matNum() const
{
	return _matNum;
}

bool Data::operator <(Data const &d)const
{
	return _matNum < d._matNum;
}