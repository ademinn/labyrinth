#include "poly.h"
#include "vector.h"

class Data
{
	Poly _poly;
	Vector _norm;
	size_t _matNum;

public:
	Data(Poly const &poly, Vector const &norm, size_t matNum);
	Data(Data const &d);
	Data();
	Data const &operator =(Data const &d);
	Poly const &poly()const;
	Vector const &norm()const;
	size_t matNum()const;
	bool operator <(Data const &d)const;
};