#pragma once

#include <math.h>

#include "Matrix.hpp"

bool is0(double val) {
	return val < 1.e-6 && val > -1.e-6;
}

int findMaxInCol(const ExMatrix& mat, const vector<int>& perms, int k) {
	int res = k;

	for (int i = k + 1; i < mat.n; i++) {
		if (abs(mat.a[perms[i]][k]) > abs(mat.a[perms[res]][k]))
			res = i;
	}

	return res;
}

void excludeX(ExMatrix& mat, const vector<int>& perms, int k) {
	double mainEl = mat.a[perms[k]][k];

	if (is0(mainEl)) throw exception("mainEl = 0");

	for (int i = k; i < mat.n; i++)
		mat.a[perms[k]][i] /= mainEl;

	mat.b[perms[k]] /= mainEl;

	for (int i = k + 1; i < mat.n; i++) {
		for (int j = k + 1; j < mat.n; j++) {
			mat.a[perms[i]][j] -= mat.a[perms[i]][k] * mat.a[perms[k]][j];
		}

		mat.b[perms[i]] -= mat.a[perms[i]][k] * mat.b[perms[k]];
	}

	for (int i = k + 1; i < mat.n; i++) {
		mat.a[perms[i]][k] = 0.;
	}
}

vector<double> findSolution(const ExMatrix& mat, const vector<int>& perms) {
	vector<double> res(mat.n);

	for (int i = mat.n - 1; i >= 0; i--) {
		double cur = mat.b[perms[i]];

		for (int j = i + 1; j < mat.n; j++) {
			cur -= mat.a[perms[i]][j] * res[j];
		}

		res[i] = cur;
	}

	return res;
}

vector<double> solve(ExMatrix mat) {
	vector<int> perms(mat.n);

	for (int i = 0; i < mat.n; i++)
		perms[i] = i;

	for (int k = 0; k < mat.n; k++) {
		int p = findMaxInCol(mat, perms, k);

		swap(perms[k], perms[p]);

		excludeX(mat, perms, k);
	}

	cout << "Triangle matrix: " << endl;
	cout << mat << endl << endl;

	return findSolution(mat, perms);
}