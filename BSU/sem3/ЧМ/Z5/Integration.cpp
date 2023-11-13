#include "Integration.hpp"

#include <cmath>

namespace Integration {
	const int n0 = 1 << 8;
	const double eps = 1e-9;

	double integrateXTrapezoid(FuncX func, double a, double b, int n) {
		double h = (b - a) / n;

		double res = (func(a) + func(b)) / 2.;

		for (int i = 1; i < n; ++i) {
			res += func(a + h * i);
		}

		return res * h;
	}

	double integrateXTrapezoid(FuncX func, double a, double b) {
		double prevI = 0;
		double curI = integrateXTrapezoid(func, a, b, n0);
		int curN = n0;

		do {
			prevI = curI;
			curN <<= 1;
			curI = integrateXTrapezoid(func, a, b, curN);
		} while (abs(prevI - curI) > 3 * eps);

		return curI;
	}

	double integrateXSimpson(FuncX func, double a, double b, int n) {
		int m = n << 1;
		double h = (b - a) / m;

		double res = func(a) + func(b);

		for (int i = 1; i <= n; ++i) {
			res += 4 * func(a + h * ((i << 1) - 1));
		}

		for (int i = 1; i < n; ++i) {
			res += 2 * func(a + h * (i << 1));
		}

		return res * h / 3.;
	}

	double integrateXSimpson(FuncX func, double a, double b) {
		double prevI = 0;
		double curI = integrateXSimpson(func, a, b, n0);
		int curN = n0;

		do {
			prevI = curI;
			curN <<= 1;
			curI = integrateXSimpson(func, a, b, curN);
		} while (abs(prevI - curI) > 15 * eps);

		return curI;
	}

	double integrateXYSimpson(FuncXY func, double a, double b, double c, double d, int n) {
		int m = n << 1;
		double h1 = (b - a) / m;
		double h2 = (d - c) / m;

		double res = 0;

		auto xFunc = [func, a, c, h1, h2](int i, int j) -> double {
			return func(a + h1 * i, c + h2 * j);
		};

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				int i2 = i << 1, j2 = j << 1;
				res += xFunc(i2, j2) + 4 * xFunc(i2 + 1, j2) + xFunc(i2 + 2, j2);
				res += 4 * xFunc(i2, j2 + 1) + 16 * xFunc(i2 + 1, j2 + 1) + 4 * xFunc(i2 + 2, j2 + 1);
				res += xFunc(i2, j2 + 2) + 4 * xFunc(i2 + 1, j2 + 2) + xFunc(i2 + 2, j2 + 2);
			}
		}

		return res * h1 * h2 / 9.;
	}

	double integrateXYSimpson(FuncXY func, double a, double b, double c, double d) {
		double prevI = 0;
		double curI = integrateXYSimpson(func, a, b, c, d, n0);
		int curN = n0;

		do {
			prevI = curI;
			curN <<= 1;
			curI = integrateXYSimpson(func, a, b, c, d, curN);
		} while (abs(prevI - curI) > 15 * eps);

		return curI;
	}
}