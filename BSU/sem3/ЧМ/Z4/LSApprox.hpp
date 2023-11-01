#pragma once

#include "../Z1/GaussSolver.hpp"

namespace LSApprox {
	vector<double> findCoef(const vector<double>& x, const vector<double>& y, unsigned int m);
	
	double countDeviation(const vector<double>& x, const vector<double>& y, const vector<double>& coefs);


	class InvalidArgument : exception {};
}