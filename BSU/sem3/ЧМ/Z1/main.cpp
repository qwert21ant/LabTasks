#include <iostream>

#include "Solve.hpp"

using namespace std;

int main() {
	int n;

	cout << "Enter matrix size: ";
	cin >> n;

	ExMatrix mat(n);

	cout << "Enter matrix A: " << endl;
	for (auto& x : mat.a)
		for (auto& y : x)
			cin >> y;
	cout << endl;

	cout << "Enter vector B: " << endl;
	for (auto& x : mat.b)
		cin >> x;
	cout << endl;

	cout << "Matrix: " << endl;
	cout << mat << endl;

	try {
		auto solution = solve(mat);

		cout << "Solution: " << endl;
		for (auto& x : solution) {
			cout << setw(8) << setprecision(4) << x << " ";
		}
		cout << endl;
	}
	catch (exception e) {
		cout << "No solution" << endl;
	}

	return 0;
}