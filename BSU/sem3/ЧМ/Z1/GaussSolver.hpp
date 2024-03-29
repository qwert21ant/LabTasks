#pragma once

#include "../common/ExMatrix.hpp"

namespace GaussSolver {
	Matrix solve(ExMatrix);

	class NoSolution : exception {};
};