#pragma once
#include <time.h>
#include "object.h"
#include "matrix.h"

Object const &cone(Point const &point, Vector const &h, double radius, size_t slices, Material const &material = NullMaterial);

Object const &icosahedron(double radius, Material const &material = NullMaterial);

Object const &sphere(double radius, char k, Material const &material = NullMaterial);

Object const &labyrinth(double radius, char level, Material const &floor = NullMaterial, Material const &walls = NullMaterial);

std::vector< std::pair<Vector, Vector> > const &getGraph();

size_t const inf = 1000000000;
