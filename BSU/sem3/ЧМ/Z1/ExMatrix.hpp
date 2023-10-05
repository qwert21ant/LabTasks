#pragma once

#include "Matrix.hpp"

class ExMatrix {
public:
	ExMatrix(size_t, size_t);

	ExMatrix(const Matrix&, const Matrix&);

	ExMatrix(const ExMatrix&);

	ExMatrix& operator =(const ExMatrix&);

	size_t getNRows() const;
	size_t getNCols() const;

	void resize(size_t, size_t);

	double& getA(size_t, size_t);
	const double& getA(size_t, size_t) const;

	double& getB(size_t);
	const double& getB(size_t) const;

	friend ostream& operator <<(ostream&, const ExMatrix&);

private:
	Matrix data;
};