#pragma once

#include <vector>

class IFunction;

using DoubleData = std::vector<double>;
using FuncMatrixType = std::vector<std::vector<IFunction*>>;

class IFunction {
public:
	virtual double calc(const DoubleData& x) const = 0;
};

class FunctionWrapper : public IFunction {
public:
	using FuncType = double (*)(const DoubleData&);

private:
	FuncType func;

public:
	FunctionWrapper(FuncType f);

	double calc(const DoubleData& x) const;

	FuncType get() const;
	void set(FuncType f);
};