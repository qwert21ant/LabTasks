#pragma once

#include "ExMatrix.hpp"

namespace GaussSolver {
	Matrix solve(ExMatrix);

	class NoSolution : exception {};
};