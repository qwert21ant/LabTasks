#pragma once

#include <vector>

class IFunction;

using DoubleData = std::vector<double>;
using FuncSystemType = std::vector<IFunction*>;
using FuncMatrixType = std::vector<std::vector<IFunction*>>;

class IFunction {
public:
	virtual double calc(const DoubleData& x) const = 0;

	static DoubleData evalSystem(const FuncSystemType& system, const DoubleData& X);
};

class FunctionWrapper : public IFunction {
	using FuncType = double (*)(const DoubleData&);

	FuncType func;

public:
	FunctionWrapper(FuncType f);

	double calc(const DoubleData& x) const;
};