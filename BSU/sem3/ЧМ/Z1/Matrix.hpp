#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct ExMatrix {
	ExMatrix(size_t n) : n(n), a(vector<vector<double>>(n, vector<double>(n))), b(vector<double>(n)) {}

	ExMatrix(const ExMatrix& mat) : n(mat.n), a(mat.a), b(mat.b) {}

	friend ostream& operator <<(ostream& out, const ExMatrix& mat) {
		for (size_t i = 0; i < mat.n; i++) {
			for (size_t j = 0; j < mat.n; j++) {
				out << setw(8) << setprecision(4) << mat.a[i][j] << " ";
			}

			out << " | " << setw(8) << setprecision(4) << mat.b[i] << endl;
		}

		return out;
	}

	size_t n;

	vector<vector<double>> a;
	vector<double> b;
};