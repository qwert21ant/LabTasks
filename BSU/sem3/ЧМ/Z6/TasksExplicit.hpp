#pragma once

#include <iostream>
#include <iomanip>

#include "EulerSolver.hpp"
#include "../Z3/NewtonSolver.hpp"

class Function1 : public IFunction {
public:
	double calc(const DoubleData& x) const override {
		return -x[0] * x[1] + sin(x[2]) / x[2];
	}
};

class Function2 : public IFunction {
	double a;

public:
	double calc(const DoubleData& x) const override {
		return -x[1] * x[1] + a * x[2] / (1 + x[2] * x[2]);
	}

	void setA(double a) {
		this->a = a;
	}
};

class TasksExplicitPerformer {
	int omegaMin = 25;
	int omegaStep = 1;
	int omegaMax = 48;

	int omegaCur = omegaMin;

	bool moreTasks = true;

	Function1 func1;
	Function2 func2;

	FunctionSystem sys{ 2 };

	DoubleData u0 = { 0, -0.412 };

	double T = 1;
	double eps = 0.01;
	double tauMax = 0.1;

	double calcA() {
		return 2.5 + omegaCur / 40;
	}

	void printResult(const vector<EulerSolver::Points>& res) {
		cout << "+------------+------------+------------+" << endl;
		cout << "|      t     |     u1     |     u2     |" << endl;
		cout << "+------------+------------+------------+" << endl;

		for (int i = 0; i < res.size(); i++) {
			cout << "| " << setw(10) << res[i].x;
			cout << " | " << setw(10) << setprecision(6) << res[i].y[0];
			cout << " | " << setw(10) << setprecision(6) << res[i].y[1] << " |" << endl;
		}

		cout << "+------------+------------+------------+" << endl;
	}

public:
	TasksExplicitPerformer() {
		NewtonSolver::kDebug = false;

		func2.setA(calcA());

		sys.set(0, &func1);
		sys.set(1, &func2);
	}

	void performTask() {
		if (!moreTasks) return;

		try {
			vector<EulerSolver::Points> res = EulerSolver::explicitMethod(u0, &sys, T, eps, tauMax);

			cout << "omega = " << omegaCur << ":" << endl;
			printResult(res);
			cout << endl;
		}
		catch (exception e) {
			cout << e.what() << endl;
		}
	}

	void nextTask() {
		if (!moreTasks) return;

		omegaCur += omegaStep;

		if (omegaCur > omegaMax) {
			moreTasks = false;
			return;
		}

		func2.setA(calcA());
	}

	bool hasMoreTasks() const {
		return moreTasks;
	}
};