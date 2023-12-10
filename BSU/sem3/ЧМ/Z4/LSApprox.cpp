#include "LSApprox.hpp"

ExMatrix createMatrix(const vector<double>& x, const vector<double>& y, unsigned int m) {
	size_t n = x.size();

	vector<double> a(2 * m, 0); // sum x^k
	vector<double> b(m + 1, 0); // sum y * x^k

	for (int i = 0; i < n; ++i) {
		double curX = x[i];

		for (int j = 0; j < 2 * m; ++j) {
			a[j] += curX;
			curX *= x[i];
		}
	}

	for (int i = 0; i < n; ++i) {
		double curX = x[i];

		b[0] += y[i];
		for (int j = 1; j <= m; ++j) {
			b[j] += y[i] * curX;
			curX *= x[i];
		}
	}

	ExMatrix res(m + 1, m + 1);

	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= m; ++j) {
			res.getA(i, j) = i + j == 0 ? n : a[i + j - 1];
		}

		res.getB(i) = b[i];
	}

	return res;
}

vector<double> LSApprox::findCoef(const vector<double>& x, const vector<double>& y, unsigned int m) {
	if (x.size() != y.size()) {
		throw LSApprox::InvalidArgument();
	}

	vector<double> res(m + 1);

	ExMatrix mat = createMatrix(x, y, m);

	Matrix coef = GaussSolver::solve(mat);

	for (int i = 0; i <= m; ++i) {
		res[i] = coef.get(i, 0);
	}

	return res;
}

double calcPolynomial(const vector<double>& coefs, double x) {
	if (coefs.empty()) {
		throw LSApprox::InvalidArgument();
	}

	size_t nCoefs = coefs.size();

	double res = coefs[0];
	double curX = x;

	for (int i = 1; i < nCoefs; ++i) {
		res += coefs[i] * curX;
		curX *= x;
	}

	return res;
}

double LSApprox::countDeviation(const vector<double>& x, const vector<double>& y, const vector<double>& coefs) {
	if (x.size() != y.size()) {
		throw LSApprox::InvalidArgument();
	}

	int n = x.size();
	int m = coefs.size();

	double res = 0;
	
	for (int i = 0; i < n; ++i) {
		double value = y[i] - calcPolynomial(coefs, x[i]);

		res += value * value;
	}

	res /= n - m;

	return sqrt(res);
}