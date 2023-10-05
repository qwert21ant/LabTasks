#include "GaussSolver.hpp"

bool is0(double val) {
	return val < 1.e-6 && val > -1.e-6;
}

int findMaxInCol(const ExMatrix& mat, const vector<int>& perms, int k) {
	int res = k;

	for (int i = k + 1; i < mat.getNRows(); i++) {
		if (abs(mat.getA(perms[i], k)) > abs(mat.getA(perms[res], k)))
			res = i;
	}

	return res;
}

void excludeX(ExMatrix& mat, const vector<int>& perms, int k) {
	double mainEl = mat.getA(perms[k], k);

	if (is0(mainEl)) throw GaussSolver::NoSolution();

	for (int i = k; i < mat.getNRows(); i++)
		mat.getA(perms[k], i) /= mainEl;

	mat.getB(perms[k]) /= mainEl;

	for (int i = k + 1; i < mat.getNRows(); i++) {
		for (int j = k + 1; j < mat.getNRows(); j++) {
			mat.getA(perms[i], j) -= mat.getA(perms[i], k) * mat.getA(perms[k], j);
		}

		mat.getB(perms[i]) -= mat.getA(perms[i], k) * mat.getB(perms[k]);
	}

	for (int i = k + 1; i < mat.getNRows(); i++) {
		mat.getA(perms[i], k) = 0.;
	}
}

Matrix findSolution(const ExMatrix& mat, const vector<int>& perms) {
	Matrix res(mat.getNRows(), 1);

	for (int i = mat.getNRows() - 1; i >= 0; i--) {
		double cur = mat.getB(perms[i]);

		for (int j = i + 1; j < mat.getNRows(); j++) {
			cur -= mat.getA(perms[i], j) * res.get(j, 0);
		}

		res.get(i, 0) = cur;
	}

	return res;
}

Matrix GaussSolver::solve(ExMatrix mat) {
	vector<int> perms(mat.getNRows());

	for (int i = 0; i < mat.getNRows(); i++)
		perms[i] = i;

	for (int k = 0; k < mat.getNRows(); k++) {
		int p = findMaxInCol(mat, perms, k);

		swap(perms[k], perms[p]);

		excludeX(mat, perms, k);
	}

	//cout << "Triangle matrix: " << endl;
	//cout << mat << endl << endl;

	return findSolution(mat, perms);
}