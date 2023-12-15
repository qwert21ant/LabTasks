#pragma once

#include "Function.hpp"
#include "Matrix.hpp"

namespace Utils {
	Matrix doubleDataToMatrix(const DoubleData& x);

	DoubleData matrixToDoubleData(const Matrix& mat);
}