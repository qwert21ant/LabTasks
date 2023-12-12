#pragma once

#include <vector>

#include "../common/Function.hpp"

using namespace std;

namespace EulerSolver {
	struct Points {
		double x;
		vector<double> y;
	};

	vector<Points> explicitMethod(const DoubleData& u0, const FuncSystemType& f, double T, double eps, double tauMax);

	vector<Points> implicitMethod(const DoubleData& u0, const FuncSystemType& f, double T, double eps, double tauMin, double tauMax);

	class IncorrectInput : exception {};
}