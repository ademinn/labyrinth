#pragma once
#include <vector>
#include "edge.h"

class Poly
{
	std::vector<size_t> vert;

public:
	Poly(size_t A = 0, size_t B = 0, size_t C = 0);
	Poly(size_t, size_t, size_t, size_t);
	Poly(std::vector<size_t> const &);
	Poly(Poly const &);
	Poly const &operator =(Poly const &p);

	size_t operator[](size_t)const;
	size_t size()const;
};

Edge compare(Poly const &, Poly const &);