#pragma once

#include "../common/Matrix.hpp"
#include "../common/FunctionSystem.hpp"

class NewtonSolver {
public:
	static bool kDebug;
	static int nMaxIter;
	static double eps1;
	static double eps2;
	static double kM;

	static DoubleData solveWithJ(IFunctionSystem*, const DoubleData&, const FuncMatrixType&);

	static DoubleData solve(IFunctionSystem*, const DoubleData&);


	class IterationsLimitExcedeed : exception {};
};