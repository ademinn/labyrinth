#pragma once
#include <stdlib.h>

class Edge
{
	size_t _a, _b;

public:
	Edge(size_t A = 0, size_t B = 0);
	Edge(Edge const &);

	Edge &operator =(Edge const &);

	size_t A()const;
	size_t B()const;
};

Edge const NullEdge;

bool operator ==(Edge const &, Edge const &);
bool operator !=(Edge const &, Edge const &);