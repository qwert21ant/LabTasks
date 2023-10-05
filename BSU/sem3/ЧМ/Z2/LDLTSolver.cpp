#pragma once

#include <math.h>

#include "LDLTSolver.hpp"

bool is0(double val) {
	return val < 1.e-6 && val > -1.e-6;
}

void factorize(ExMatrix& mat) {
	// w\o additional a matrix
	/*for (int j = 0; j < mat.getNRows(); j++) {
		double val = mat.getA(j, j);
		for (int k = 0; k < j; k++) {
			val -= mat.getA(j, k) * mat.getA(j, k) * mat.getA(k, k);
		}

		mat.getA(j, j) = val;

		for (int i = j + 1; i < mat.getNRows(); i++) {
			double val = mat.getA(i, j);
			for (int k = 0; k < j; k++) {
				val -= mat.getA(i, k) * mat.getA(j, k) * mat.getA(k, k);
			}

			mat.getA(i, j) = val / mat.getA(j, j);
		}
	}*/

	for (int j = 0; j < mat.getNRows(); j++) {
		for (int i = j + 1; i < mat.getNRows(); i++) {
			double val = mat.getA(i, j);
			for (int k = 0; k < j; k++) {
				val -= mat.getA(k, i) * mat.getA(j, k);
			}

			mat.getA(j, i) = val;
		}

		double val = mat.getA(j, j);
		for (int k = 0; k < j; k++) {
			val -= mat.getA(k, j) * mat.getA(j, k);
		}

		mat.getA(j, j) = val;

		for (int i = j + 1; i < mat.getNRows(); i++) {
			mat.getA(i, j) = mat.getA(j, i) / mat.getA(j, j);
		}
	}
}

void defactorize(ExMatrix& mat) {
	for (int j = mat.getNRows() - 1; j >= 0; j--) {
		for (int i = mat.getNRows() - 1; i >= j; i--) {
			double val = 0;
			for (int k = 0; k < j; k++) {
				val += mat.getA(i, k) * mat.getA(j, k) * mat.getA(k, k);
			}

			val += (i == j ? 1. : mat.getA(i, j)) * mat.getA(j, j);

			mat.getA(i, j) = mat.getA(j, i) = val;
		}
	}
}

void solveL(ExMatrix& mat) {
	for (int i = 0; i < mat.getNRows(); i++) {
		for (int j = 0; j < i; j++) {
			mat.getB(i) -= mat.getA(i, j) * mat.getB(j);
		}
	}
}

void solveD(ExMatrix& mat) {
	for (int i = 0; i < mat.getNRows(); i++) {
		mat.getB(i) /= mat.getA(i, i);
	}
}

void solveLT(ExMatrix& mat) {
	for (int i = mat.getNRows() - 1; i >= 0; i--) {
		for (int j = i + 1; j < mat.getNRows(); j++) {
			mat.getB(i) -= mat.getA(j, i) * mat.getB(j);
		}
	}
}

Matrix LDLTSolver::solve(ExMatrix mat) {
	factorize(mat);

	solveL(mat);
	solveD(mat);
	solveLT(mat);

	Matrix res(mat.getNRows(), 1);

	for (int i = 0; i < res.getNRows(); i++) {
		res.get(i, 0) = mat.getB(i);
	}

	return res;
}