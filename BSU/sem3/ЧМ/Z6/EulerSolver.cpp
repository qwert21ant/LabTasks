#include "EulerSolver.hpp"

using namespace EulerSolver;

DoubleData evalFuncSystem(const FuncSystemType& f, const DoubleData& u, double t) {
	DoubleData x = u;
	x.push_back(t);

	return IFunction::evalSystem(f, x);
}

double findTau(const DoubleData& fVal, double eps, double tauMax) {
	double res = 1e9;

	for (int i = 0; i < fVal.size(); ++i) {
		double cur = eps / floor(abs(fVal[i]) + eps / tauMax);

		res = min(res, cur);
	}

	return res;
}

void addStep(DoubleData& yCur, const DoubleData& fVal, double tau) {
	for (int i = 0; i < yCur.size(); ++i) {
		yCur[i] += tau * fVal[i];
	}
}

vector<Points> EulerSolver::explicitMethod(
	const DoubleData& u0, const FuncSystemType& f,
	double T, double eps, double tauMax
) {
	int n = u0.size();

	if (n != f.size()) {
		throw IncorrectInput();
	}

	vector<Points> res;

	double tCur = 1e-9;
	vector<double> yCur = u0;

	do {
		res.push_back({ tCur, yCur });

		vector<double> fVal = evalFuncSystem(f, yCur, tCur);
		double tau = findTau(fVal, eps, tauMax);

		addStep(yCur, fVal, tau);
		tCur += tau;
	} while (tCur < T);

	return res;
}

vector<Points> EulerSolver::implicitMethod(
	const DoubleData& u0, const FuncSystemType& f,
	double T, double eps, double tauMin, double tauMax
) {
	int n = u0.size();

	if (n != f.size()) {
		throw IncorrectInput();
	}

	vector<Points> res;

	double tCur = 0;
	vector<double> yPrev = u0;
	vector<double> yCur = u0;
	vector<double> yNext = u0;

	do {
		res.push_back({ tCur, yCur });

		vector<double> fVal = evalFuncSystem(f, yCur, tCur);
		double tau = findTau(fVal, eps, tauMax);

		addStep(yCur, fVal, tau);
		tCur += tau;
	} while (tCur < T);

	return res;
}