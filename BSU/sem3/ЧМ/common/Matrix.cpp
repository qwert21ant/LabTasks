#include "Matrix.hpp"

Matrix::Matrix() : n(0), m(0), data(0) {}

Matrix::Matrix(size_t n, size_t m) : n(n), m(m), data(n, vector<double>(m)) {}

Matrix::Matrix(const Matrix& mat) : n(mat.n), m(mat.m), data(mat.data) {}

Matrix& Matrix::operator =(const Matrix& mat) {
	if (&mat == this) return *this;

	resize(mat.n, mat.m);

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			data[i][j] = mat.data[i][j];
		}
	}

	return *this;
}

size_t Matrix::getNRows() const { return n; }
size_t Matrix::getNCols() const { return m; }

void Matrix::resize(size_t n, size_t m) {
	this->n = n;
	this->m = m;

	data.resize(n);

	for (size_t i = 0; i < n; i++) {
		data[i].resize(m);
	}
}

double& Matrix::get(size_t i, size_t j) {
	if (i >= n || j >= m) {
		throw OutOfRange();
	}

	return data[i][j];
}

const double& Matrix::get(size_t i, size_t j) const {
	if (i >= n || j >= m) {
		throw OutOfRange();
	}

	return data[i][j];
}

Matrix& Matrix::add(const Matrix& mat) {
	if (n != mat.n || m != mat.m) {
		throw IncorrectDimensions();
	}

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			data[i][j] += mat.data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::subtract(const Matrix& mat) {
	if (n != mat.n || m != mat.m) {
		throw IncorrectDimensions();
	}

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			data[i][j] -= mat.data[i][j];
		}
	}

	return *this;
}

Matrix& Matrix::multiply(const Matrix& mat) {
	if (m != mat.n) {
		throw IncorrectDimensions();
	}

	vector<vector<double>> newData = vector<vector<double>>(n, vector<double>(mat.m, 0));

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < mat.m; j++) {
			for (size_t k = 0; k < m; k++) {
				newData[i][j] += data[i][k] * mat.data[k][j];
			}
		}
	}

	m = mat.m;
	data = newData;

	return *this;
}

double Matrix::norm() const {
	double res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res = max(res, abs(data[i][j]));
		}
	}

	return res;
}

bool Matrix::isSquare() const {
	return n == m;
}

bool Matrix::isSymmetric() const {
	if (!isSquare()) return false;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (data[i][j] != data[j][i]) {
				return false;
			}
		}
	}

	return true;
}

Matrix operator +(Matrix l, const Matrix& r) {
	l.add(r);

	return l;
}

Matrix operator -(Matrix l, const Matrix& r) {
	l.subtract(r);

	return l;
}

Matrix operator *(Matrix l, const Matrix& r) {
	l.multiply(r);

	return l;
}

ostream& operator <<(ostream& out, const Matrix& mat) {
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < mat.m; j++) {
			out << setw(10) << setprecision(6) << mat.data[i][j] << " ";
		}
		out << endl;
	}
	return out;
}