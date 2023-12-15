#pragma once

#include <iostream>

#include "EulerSolver.hpp"
#include "../common/Matrix.hpp"
#include "../common/Utils.hpp"

using namespace std;
using namespace Utils;

class AuxFunctionSystem : public IFunctionSystem {
public:
	Matrix A;
	Matrix b;

	AuxFunctionSystem() {};

	DoubleData calc(const DoubleData& x) const override {
		DoubleData x1 = x;
		x1.pop_back();

		return matrixToDoubleData(A * doubleDataToMatrix(x1) - b);
	}

	size_t size() const override {
		return 3;
	}
};

class TasksImplicitPerformer {
	AuxFunctionSystem sys;

	DoubleData u0 = { 10, 22, 9 };

	double T = 1;
	double eps = 0.01;
	double tauMin = 0.01;
	double tauMax = 0.1;

	void printResult(const vector<EulerSolver::Points>& res) {
		cout << "+------------+------------+------------+------------+" << endl;
		cout << "|      t     |     u1     |     u2     |     u3     |" << endl;
		cout << "+------------+------------+------------+------------+" << endl;

		for (int i = 0; i < res.size(); i++) {
			cout << "| " << setw(10) << res[i].x;
			cout << " | " << setw(10) << setprecision(6) << res[i].y[0];
			cout << " | " << setw(10) << setprecision(6) << res[i].y[1];
			cout << " | " << setw(10) << setprecision(6) << res[i].y[2] << " |" << endl;
		}

		cout << "+------------+------------+------------+------------+" << endl;
	}

	Matrix calcA(double l1, double l2, double l3) {
		Matrix A(3, 3);

		A.get(0, 0) = 2 * l1 + 4 * l2;
		A.get(0, 1) = A.get(0, 2) = A.get(1, 0) = A.get(2, 0) = 2 * (l1 - l2);
		A.get(1, 1) = A.get(2, 2) = 2 * l1 + l2 + 3 * l3;
		A.get(1, 2) = A.get(2, 1) = 2 * l1 + l2 - 3 * l3;

		A = A * (1. / 6.);

		return A;
	}

	Matrix calcB(double l1, double l2, double l3) {
		Matrix b(3, 1);

		b.get(0, 0) = 4 * l1 + 2 * l2;
		b.get(1, 0) = 4 * l1 - l2 - 9 * l3;
		b.get(2, 0) = 4 * l1 - l2 + 9 * l3;

		b = b * (-1. / 6.);

		return b;
	}

public:
	TasksImplicitPerformer(double l1, double l2, double l3) {
		sys.A = calcA(l1, l2, l3);
		sys.b = calcB(l1, l2, l3);
	}

	void performTask() {
		try {
			vector<EulerSolver::Points> res = EulerSolver::implicitMethod(u0, &sys, T, eps, tauMin, tauMax);

			printResult(res);
			cout << endl;
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}
};