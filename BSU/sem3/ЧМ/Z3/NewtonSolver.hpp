#pragma once

#include "../common/Matrix.hpp"

class NewtonSolver {
public:
	using ArgType = const Matrix&;
	using FuncType = double (*)(ArgType);
	using FuncSystemType = vector<FuncType>;
	using FuncMatrixType = vector<vector<FuncType>>;

	static bool kDebug;
	static int nMaxIter;
	static double eps1;
	static double eps2;
	static double kM;

	static Matrix solveWithJ(FuncSystemType, ArgType, FuncMatrixType);

	static Matrix solve(FuncSystemType, ArgType);


	class IterationsLimitExcedeed : exception {};
};