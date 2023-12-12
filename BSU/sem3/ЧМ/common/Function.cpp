#include "Function.hpp"

DoubleData IFunction::evalSystem(const FuncSystemType& system, const DoubleData& X) {
	DoubleData res(system.size());

	for (int i = 0; i < res.size(); i++) {
		res[i] = system[i]->calc(X);
	}

	return res;
}

FunctionWrapper::FunctionWrapper(FuncType f) {
	func = f;
}

double FunctionWrapper::calc(const DoubleData& x) const {
	return func(x);
}