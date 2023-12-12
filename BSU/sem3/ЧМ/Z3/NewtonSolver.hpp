#pragma once

#include "../common/Matrix.hpp"
#include "../common/Function.hpp"

class NewtonSolver {
public:
	static bool kDebug;
	static int nMaxIter;
	static double eps1;
	static double eps2;
	static double kM;

	static DoubleData solveWithJ(const FuncSystemType&, const DoubleData&, const FuncMatrixType&);

	static DoubleData solve(const FuncSystemType&, const DoubleData&);


	class IterationsLimitExcedeed : exception {};
};