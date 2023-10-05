#include <iostream>

#include "LDLTSolver.hpp"

using namespace std;

ExMatrix createMat(double l1, double l2, double l3) {
	ExMatrix res(3, 3);

	res.getA(0, 0) = 2 * l1 + 4 * l2;
	res.getA(1, 1) = res.getA(2, 2) = 2 * l1 + l2 + 3 * l3;

	res.getA(0, 1) = res.getA(1, 0) = 2 * (l1 - l2);
	res.getA(0, 2) = res.getA(2, 0) = 2 * (l1 - l2);
	res.getA(1, 2) = res.getA(2, 1) = 2 * l1 + l2 - 3 * l3;

	res.getB(0) = -4 * l1 - 2 * l2;
	res.getB(1) = -4 * l1 + l2 + 9 * l3;
	res.getB(2) = -4 * l1 + l2 - 9 * l3;

	return res;
}

int main() {
	double l1, l2, l3;
	
	cout << "Enter 3 coeff: ";
	cin >> l1 >> l2 >> l3;

	ExMatrix mat = createMat(l1, l2, l3);

	cout << "Matrix: " << endl;
	cout << mat << endl;

	Matrix X;

	try {
		X = LDLTSolver::solve(mat);

		cout << "Solution: " << endl;
		cout << X << endl;
	} catch (LDLTSolver::NoSolution e) {
		cout << "No solution" << endl;
		return 0;
	}

	return 0;
}