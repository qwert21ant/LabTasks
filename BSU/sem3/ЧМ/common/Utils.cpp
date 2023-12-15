#include "Utils.hpp"

Matrix Utils::doubleDataToMatrix(const DoubleData& x) {
	Matrix res(x.size(), 1);

	for (int i = 0; i < x.size(); ++i) {
		res.get(i, 0) = x[i];
	}

	return res;
}

DoubleData Utils::matrixToDoubleData(const Matrix& mat) {
	DoubleData res(mat.getNRows());

	for (int i = 0; i < mat.getNRows(); ++i) {
		res[i] = mat.get(i, 0);
	}

	return res;
}