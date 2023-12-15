#pragma once

#include <vector>

#include "Function.hpp"

class IFunctionSystem {
public:
	virtual DoubleData calc(const DoubleData& x) const = 0;

	virtual size_t size() const = 0;
};

class FunctionSystem : public IFunctionSystem {
	std::vector<IFunction*> func;

public:
	FunctionSystem(const std::vector<IFunction*>& f);
	FunctionSystem(size_t sz);

	DoubleData calc(const DoubleData& x) const;

	size_t size() const;

	IFunction* get(size_t ind) const;
	void set(size_t ind, IFunction* f);
};