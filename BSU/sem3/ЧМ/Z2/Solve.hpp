#pragma once

#include <math.h>

#include "Matrix.hpp"

bool is0(double val) {
	return val < 1.e-6 && val > -1.e-6;
}

void factorize(ExMatrix& mat) {
	// w\o additional a matrix
	/*for (int j = 0; j < mat.n; j++) {
		double val = mat.a[j][j];
		for (int k = 0; k < j; k++) {
			val -= mat.a[j][k] * mat.a[j][k] * mat.a[k][k];
		}

		mat.a[j][j] = val;

		for (int i = j + 1; i < mat.n; i++) {
			double val = mat.a[i][j];
			for (int k = 0; k < j; k++) {
				val -= mat.a[i][k] * mat.a[j][k] * mat.a[k][k];
			}

			mat.a[i][j] = val / mat.a[j][j];
		}
	}*/

	for (int j = 0; j < mat.n; j++) {
		for (int i = j + 1; i < mat.n; i++) {
			double val = mat.a[i][j];
			for (int k = 0; k < j; k++) {
				val -= mat.a[k][i] * mat.a[j][k];
			}

			mat.a[j][i] = val;
		}

		double val = mat.a[j][j];
		for (int k = 0; k < j; k++) {
			val -= mat.a[k][j] * mat.a[j][k];
		}

		mat.a[j][j] = val;

		for (int i = j + 1; i < mat.n; i++) {
			mat.a[i][j] = mat.a[j][i] / mat.a[j][j];
		}
	}
}

void defactorize(ExMatrix& mat) {
	for (int j = mat.n - 1; j >= 0; j--) {
		for (int i = mat.n - 1; i >= j; i--) {
			double val = 0;
			for (int k = 0; k < j; k++) {
				val += mat.a[i][k] * mat.a[j][k] * mat.a[k][k];
			}

			val += (i == j ? 1. : mat.a[i][j]) * mat.a[j][j];

			mat.a[i][j] = mat.a[j][i] = val;
		}
	}
}

void solveL(ExMatrix& mat) {
	for (int i = 0; i < mat.n; i++) {
		for (int j = 0; j < i; j++) {
			mat.b[i] -= mat.a[i][j] * mat.b[j];
		}
	}
}

void solveD(ExMatrix& mat) {
	for (int i = 0; i < mat.n; i++) {
		mat.b[i] /= mat.a[i][i];
	}
}

void solveLT(ExMatrix& mat) {
	for (int i = mat.n - 1; i >= 0; i--) {
		for (int j = i + 1; j < mat.n; j++) {
			mat.b[i] -= mat.a[j][i] * mat.b[j];
		}
	}
}

vector<double> solve(ExMatrix mat) {
	factorize(mat);

	solveL(mat);
	solveD(mat);
	solveLT(mat);

	return mat.b;
}