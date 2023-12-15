#include "EulerSolver.hpp"

#include "../Z3/NewtonSolver.hpp"

using namespace EulerSolver;

DoubleData evalFuncSystem(IFunctionSystem* f, const DoubleData& u, double t) {
	DoubleData x = u;
	x.push_back(t);

	return f->calc(x);
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
	const DoubleData& u0, IFunctionSystem* sys,
	double T, double eps, double tauMax
) {
	int n = u0.size();

	if (n != sys->size()) {
		throw IncorrectInput();
	}

	vector<Points> res;

	double tCur = 1e-9;
	vector<double> yCur = u0;

	do {
		res.push_back({ tCur, yCur });

		vector<double> fVal = evalFuncSystem(sys, yCur, tCur);
		double tau = findTau(fVal, eps, tauMax);

		addStep(yCur, fVal, tau);
		tCur += tau;
	} while (tCur < T);

	return res;
}



class EulerImplicitAuxFunctionSystem : public IFunctionSystem {
	DoubleData yCur;
	double tau = 0;
	double tNext = 0;
	IFunctionSystem* sys;

public:
	EulerImplicitAuxFunctionSystem(IFunctionSystem* sys) {
		this->sys = sys;
	}

	void update(const DoubleData& yCur, double tauCur, double tNext) {
		this->yCur = yCur;
		this->tau = tauCur;
		this->tNext = tNext;
	}

	DoubleData calc(const DoubleData& x) const override {
		DoubleData x1 = x;
		x1.push_back(tNext);

		DoubleData res = sys->calc(x1); // initially stores f(x, tNext)

		for (int i = 0; i < res.size(); ++i) {
			res[i] = x[i] - yCur[i] - tau * res[i];
		}

		return res;
	}

	size_t size() const override {
		return sys->size();
	}
};

DoubleData findEps(const DoubleData& yPrev, const DoubleData& yCur, const DoubleData& yNext, double tauPrev, double tauCur) {
	DoubleData res(yCur.size());

	for (int i = 0; i < res.size(); ++i) {
		res[i] = -tauCur / (tauCur + tauPrev) * (yNext[i] - yCur[i] - tauCur / tauPrev * (yCur[i] - yPrev[i]));
	}

	return res;
}

double findTau2(const DoubleData& epsCur, double eps, double tauCur) {
	double res = 1e9;

	for (int i = 0; i < epsCur.size(); ++i) {
		double cur = 0;

		if (abs(epsCur[i]) > eps / 4.) {
			cur = tauCur;
		} else {
			cur = 2 * tauCur;
		}

		res = min(res, cur);
	}

	return res;
}

vector<Points> EulerSolver::implicitMethod(
	const DoubleData& u0, IFunctionSystem* sys,
	double T, double eps, double tauMin, double tauMax
) {
	int n = u0.size();

	if (n != sys->size()) {
		throw IncorrectInput();
	}

	NewtonSolver::kDebug = false;

	vector<Points> res;

	double tCur = 0;
	double tauPrev = tauMin;
	double tauCur = tauMin;

	vector<double> yPrev = u0;
	vector<double> yCur = u0;
	vector<double> yNext = u0;

	EulerImplicitAuxFunctionSystem sysAux(sys);

	res.push_back({ tCur, yCur });
	do {
		double tNext = tCur + tauCur;

		sysAux.update(yCur, tauCur, tNext);
		try {
			yNext = NewtonSolver::solve(&sysAux, u0);
		}
		catch (exception e) {
			cout << e.what() << endl;
			throw;
		}

		DoubleData epsCur = findEps(yPrev, yCur, yNext, tauPrev, tauCur);

		bool skip = false;
		for (int i = 0; i < n; ++i) {
			if (abs(epsCur[i]) > eps) {
				skip = true;
				break;
			}
		}

		if (skip) {
			tauCur /= 2;
			yNext = yCur;

			continue;
		}
		
		double tauNext = min(findTau2(epsCur, eps, tauCur), tauMax);

		res.push_back({ tCur, yCur });

		yPrev = yCur;
		yCur = yNext;
		tauPrev = tauCur;
		tauCur = tauNext;
		tCur = tNext;
	} while (tCur < T);

	return res;
}