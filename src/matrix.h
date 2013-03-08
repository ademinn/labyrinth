#pragma once
#include <vector>
#include "vector.h"

class Matrix
{
	std::vector< std::vector<double> > _m;

public:
		double *d;
	Matrix(std::vector< std::vector<double> > const &);
	Matrix();
	Matrix(Matrix const &);
	Matrix(Vector const &v1, double ang);
	Matrix(Vector const &v);
	Matrix &operator =(Matrix const &);
	~Matrix();
	Vector operator *(Vector const &);
	Matrix &operator *=(double const c);
	Matrix &operator +=(Matrix const &);
	friend Matrix operator -(Matrix const &);
	Matrix &operator *=(Matrix const &);
	double *get()const;
};

Matrix const I;
Matrix operator -(Matrix const &, Matrix const &);
Matrix operator +(Matrix const &, Matrix const &);
Matrix operator *(double const, Matrix const &);
Matrix rotate(Vector const &, Vector const &);
Matrix operator *(Matrix const &, Matrix const &);