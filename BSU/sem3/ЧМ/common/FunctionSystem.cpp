#include "FunctionSystem.hpp"

FunctionSystem::FunctionSystem(const std::vector<IFunction*>& f) {
	func = f;
}

FunctionSystem::FunctionSystem(size_t sz) {
	func.resize(sz, nullptr);
}

DoubleData FunctionSystem::calc(const DoubleData& x) const {
	DoubleData res(func.size());

	for (int i = 0; i < res.size(); i++) {
		res[i] = func[i]->calc(x);
	}

	return res;
}

size_t FunctionSystem::size() const {
	return func.size();
}

IFunction* FunctionSystem::get(size_t ind) const {
	return func[ind];
}

void FunctionSystem::set(size_t ind, IFunction* f) {
	func[ind] = f;
}