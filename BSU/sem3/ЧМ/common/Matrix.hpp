#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(size_t, size_t);

	Matrix(const Matrix&);

	Matrix& operator =(const Matrix&);

	size_t getNRows() const;
	size_t getNCols() const;

	void resize(size_t, size_t);

	double& get(size_t, size_t);
	const double& get(size_t, size_t) const;

	Matrix& add(const Matrix&);
	Matrix& subtract(const Matrix&);
	Matrix& multiply(const Matrix&);

	double norm() const;

	bool isSquare() const;
	bool isSymmetric() const;

	friend Matrix operator +(Matrix, const Matrix&);
	friend Matrix operator -(Matrix, const Matrix&);
	friend Matrix operator *(Matrix, const Matrix&);

	friend ostream& operator <<(ostream&, const Matrix&);

private:
	size_t n, m;

	vector<vector<double>> data;

public:
	class OutOfRange : exception {};
	class IncorrectDimensions : exception {};
};