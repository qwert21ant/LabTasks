/*
Input example:

3
0.14 1.07 0.64
0.24 -0.83 0.43
-0.84 0.56 -0.38
1.11 0.48 -0.83
*/

#include <iostream>

#include "GaussSolver.hpp"

using namespace std;

int main() {
	int n;

	cout << "Enter matrix size: ";
	cin >> n;

	Matrix A(n, n), B(n, 1);

	cout << "Enter matrix A: " << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A.get(i, j);
	cout << endl;

	cout << "Enter vector B: " << endl;
	for (int i = 0; i < n; i++)
		cin >> B.get(i, 0);
	cout << endl;

	ExMatrix mat(A, B);

	cout << "Matrix: " << endl;
	cout << mat << endl;

	Matrix X;

	try {
		X = GaussSolver::solve(mat);

		cout << "Solution: " << endl;
		cout << X << endl;
	} catch (GaussSolver::NoSolution e) {
		cout << "No solution" << endl;
		return 0;
	}
	
	Matrix F = A * X - B;

	cout << "F vector: " << endl;
	cout << F << endl;

	cout << "F norm: " << F.norm() << endl;

	mat = ExMatrix(A, A * X);

	Matrix Xt;

	try {
		Xt = GaussSolver::solve(mat);

		cout << "Solution for 2nd system: " << endl;
		cout << Xt << endl;
	} catch (GaussSolver::NoSolution e) {
		cout << "No solution 2nd system" << endl;
		return 0;
	}

	double delta = (Xt - X).norm() / X.norm();
	cout << "Relative error: " << delta << endl;

	return 0;
}