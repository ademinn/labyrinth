#pragma once
#include <vector>
#include "edge.h"

class Face
{
	std::vector<size_t> vert;

public:
	Face(size_t A = 0, size_t B = 0, size_t C = 0);
	Face(size_t, size_t, size_t, size_t);
	Face(std::vector<size_t> const &);
	Face(Face const &);

	size_t operator[](size_t)const;
	size_t size()const;
};

Edge compare(Face const &, Face const &);