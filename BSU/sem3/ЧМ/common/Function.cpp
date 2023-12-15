#include "Function.hpp"

FunctionWrapper::FunctionWrapper(FuncType f) {
	func = f;
}

double FunctionWrapper::calc(const DoubleData& x) const {
	return func(x);
}

FunctionWrapper::FuncType FunctionWrapper::get() const {
	return func;
}

void FunctionWrapper::set(FuncType f) {
	func = f;
}