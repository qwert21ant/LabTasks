#include "ExMatrix.hpp"

ExMatrix::ExMatrix(size_t n, size_t m) : data(Matrix(n, m+1)) {}

ExMatrix::ExMatrix(const Matrix& A, const Matrix& B) {
	if (A.getNRows() != B.getNRows() || B.getNCols() != 1) {
		throw Matrix::IncorrectDimensions();
	}

	data = Matrix(A.getNRows(), A.getNCols() + 1);

	for (size_t i = 0; i < getNRows(); i++) {
		for (size_t j = 0; j < getNCols(); j++) {
			data.get(i, j) = A.get(i, j);
		}

		data.get(i, getNCols()) = B.get(i, 0);
	}
}

ExMatrix::ExMatrix(const ExMatrix& mat) : data(mat.data) {}

ExMatrix& ExMatrix::operator =(const ExMatrix& mat) {
	if (&mat == this) return *this;

	resize(mat.getNRows(), mat.getNCols());

	for (size_t i = 0; i < getNRows(); i++) {
		for (size_t j = 0; j < data.getNCols(); j++) {
			data.get(i, j) = mat.data.get(i, j);
		}
	}

	return *this;
}

size_t ExMatrix::getNRows() const { return data.getNRows(); }
size_t ExMatrix::getNCols() const { return data.getNCols() - 1; }

void ExMatrix::resize(size_t n, size_t m) {
	if (n == 0 || m == 0) {
		throw Matrix::IncorrectDimensions();
	}

	data.resize(n, m + 1);
}

double& ExMatrix::getA(size_t i, size_t j) {
	if (i >= getNRows() || j >= getNCols()) {
		throw Matrix::OutOfRange();
	}

	return data.get(i, j);
}

const double& ExMatrix::getA(size_t i, size_t j) const {
	if (i >= getNRows() || j >= getNCols()) {
		throw Matrix::OutOfRange();
	}

	return data.get(i, j);
}

double& ExMatrix::getB(size_t i) {
	if (i >= getNRows()) {
		throw Matrix::OutOfRange();
	}

	return data.get(i, getNRows());
}

const double& ExMatrix::getB(size_t i) const {
	if (i >= getNRows()) {
		throw Matrix::OutOfRange();
	}

	return data.get(i, getNRows());
}

ostream& operator <<(ostream& out, const ExMatrix& mat) {
	for (size_t i = 0; i < mat.getNRows(); i++) {
		for (size_t j = 0; j < mat.getNCols(); j++) {
			out << setw(10) << setprecision(6) << mat.getA(i, j) << " ";
		}

		out << " | " << setw(10) << setprecision(6) << mat.getB(i) << endl;
	}

	return out;
}