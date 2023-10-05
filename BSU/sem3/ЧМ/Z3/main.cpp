#include <iostream>

#include "NewtonSolver.hpp"

using namespace std;

double func1(NewtonSolver::ArgType x) { return sin(x.get(0, 0) + 1) - x.get(1, 0) - 1; }
double func2(NewtonSolver::ArgType x) { return 2 * x.get(0, 0) + cos(x.get(1, 0)) - 2; }

double J11(NewtonSolver::ArgType x) { return cos(x.get(0, 0) + 1); }
double J12(NewtonSolver::ArgType x) { return -1; }
double J21(NewtonSolver::ArgType x) { return 2; }
double J22(NewtonSolver::ArgType x) { return -sin(x.get(1, 0)); }

int main() {
	NewtonSolver::FuncSystemType system = { func1, func2 };

	NewtonSolver::FuncMatrixType J = {
		{ J11, J12 },
		{ J21, J22 },
	};

	Matrix X0(2, 1);
	X0.get(0, 0) = 1;
	X0.get(1, 0) = 1;


	NewtonSolver::kM = 0.01;
	NewtonSolver::eps1 = 1e-9;
	NewtonSolver::eps2 = 1e-9;


	cout << "Solve with J: " << endl;
	try {
		Matrix X = NewtonSolver::solveWithJ(system, X0, J);

		cout << "Solution: " << endl;
		cout << X << endl;
	} catch (exception e) {
		cout << "Exception" << endl;
		cout << e.what() << endl;
	}

	cout << "Solve without J: " << endl;
	try {
		Matrix X = NewtonSolver::solve(system, X0);

		cout << "Solution: " << endl;
		cout << X << endl;
	}
	catch (exception e) {
		cout << "Exception" << endl;
		cout << e.what() << endl;
	}

	return 0;
}