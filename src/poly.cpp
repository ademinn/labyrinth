#include "poly.h"

Poly::Poly(size_t A, size_t B, size_t C)
{
	vert.push_back(A);
	vert.push_back(B);
	vert.push_back(C);
}

Poly::Poly(size_t A, size_t B, size_t C, size_t D)
{
	vert.push_back(A);
	vert.push_back(B);
	vert.push_back(C);
	vert.push_back(D);
}

Poly::Poly(std::vector<size_t> const &v)
	: vert(v)
{
}

Poly::Poly(Poly const &f)
	: vert(f.vert)
{
}

Poly const &Poly::operator =(const Poly &p)
{
	vert = p.vert;
	return *this;
}

size_t Poly::operator[](size_t i)const
{
	return vert[i];
}

size_t Poly::size()const
{
	return vert.size();
}

Edge compare(Poly const &f1, Poly const &f2)
{
	for(size_t i1 = 0; i1 < f1.size() - 1; ++i1)
		for(size_t i2 = 0; i2 < f2.size(); ++i2)
			if(f1[i1] == f2[i2])
				for(size_t j1 = i1 + 1; j1 < f1.size(); ++j1)
					for(size_t j2 = 0; j2 < f2.size(); ++j2)
						if(f1[j1] == f2[j2])
							return Edge(f1[i1], f1[j1]);
	return NullEdge;
}
