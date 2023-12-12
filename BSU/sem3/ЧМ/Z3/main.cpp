#include <iostream>

#include "NewtonSolver.hpp"

using namespace std;

double func1(const DoubleData& x) { return sin(x[0] + 1) - x[1] - 1; }
double func2(const DoubleData& x) { return 2 * x[0] + cos(x[1]) - 2; }

double J11(const DoubleData& x) { return cos(x[0] + 1); }
double J12(const DoubleData& x) { return -1; }
double J21(const DoubleData& x) { return 2; }
double J22(const DoubleData& x) { return -sin(x[1]); }

int main() {
	FuncSystemType system = { new FunctionWrapper(func1), new FunctionWrapper(func2) };

	FuncMatrixType J = {
		{ new FunctionWrapper(J11), new FunctionWrapper(J12) },
		{ new FunctionWrapper(J21), new FunctionWrapper(J22) },
	};

	DoubleData X0 = { 1, 1 };


	NewtonSolver::kM = 0.01;
	NewtonSolver::eps1 = 1e-9;
	NewtonSolver::eps2 = 1e-9;


	cout << "Solve with J: " << endl;
	try {
		DoubleData X = NewtonSolver::solveWithJ(system, X0, J);

		cout << "Solution: " << endl;
		for (auto x : X) cout << x << " ";
		cout << endl;
	} catch (exception e) {
		cout << "Exception" << endl;
		cout << e.what() << endl;
	}

	cout << "Solve without J: " << endl;
	try {
		DoubleData X = NewtonSolver::solve(system, X0);

		cout << "Solution: " << endl;
		for (auto x : X) cout << x << " ";
		cout << endl;
	}
	catch (exception e) {
		cout << "Exception" << endl;
		cout << e.what() << endl;
	}

	return 0;
}