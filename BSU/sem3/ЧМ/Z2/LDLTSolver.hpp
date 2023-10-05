#pragma once

#include "../common/ExMatrix.hpp"

namespace LDLTSolver {
	Matrix solve(ExMatrix);

	class IncorrectInput : exception {};
	class NoSolution : exception {};
};