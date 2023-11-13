#pragma once

namespace Integration {
	using FuncX = double (*)(double);
	using FuncXY = double (*)(double, double);

	double integrateXTrapezoid(FuncX func, double a, double b);
	double integrateXSimpson(FuncX func, double a, double b);
	double integrateXYSimpson(FuncXY func, double a, double b, double c, double d);
}