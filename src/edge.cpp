#include "edge.h"

Edge::Edge(size_t A, size_t B)
	: _a(A), _b(B)
{
}

Edge::Edge(Edge const &e)
	: _a(e._a), _b(e._b)
{
}

Edge &Edge::operator =(Edge const &e)
{
	_a = e._a;
	_b = e._b;
	return (*this);
}

size_t Edge::A()const
{
	return _a;
}

size_t Edge::B()const
{
	return _b;
}

bool operator ==(Edge const &e1, Edge const &e2)
{
	return ((e1.A() == e2.A()) && (e1.B() == e2.B()));
}

bool operator !=(Edge const &e1, Edge const &e2)
{
	return !(e1 == e2);
}