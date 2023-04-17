#pragma once

#include <vector>
#include <type_traits>

using namespace std;

template <bool C, class T>
struct const_if {};

template <class T>
struct const_if<true, T> {
	using type = const T;
};

template <class T>
struct const_if<false, T> {
	using type = T;
};

template <bool C, class T>
using const_if_t = typename const_if<C, T>::type;



template <class T>
class Matrix;

template <class T, bool C>
class MatrixProxy {
public:
	~MatrixProxy() = default;

	const_if_t<C, T>& operator[](size_t ind) {
		return data[n * ind1 + ind];
	}

	friend class Matrix<T>;

private:
	MatrixProxy(const_if_t<C, vector<T>>& data, size_t n, size_t ind) : data(data), n(n), ind1(ind) {};

	const_if_t<C, vector<T>>& data;
	size_t n;
	size_t ind1;
};

template <class T>
class Matrix {
public:
	Matrix(size_t n, size_t m) : n(n), m(m), data(n* m, T()) {};
	~Matrix() = default;

	auto GetDimensions() const {
		return make_pair(n, m);
	}

	MatrixProxy<T, false> operator [](size_t ind) {
		return MatrixProxy<T, false>(data, n, ind);
	}
	MatrixProxy<T, true> operator [](size_t ind) const {
		return MatrixProxy<T, true>(data, n, ind);
	}

private:
	size_t n, m;
	vector<T> data;
};

template <class T>
Matrix<T> operator *(const Matrix<T>& l, const Matrix<T>& r) {
	auto d1 = l.GetDimensions();
	auto d2 = r.GetDimensions();

	Matrix<T> res(d1.first, d2.second);
	if (d1.second != d2.first)
		return res;

	for (int i = 0; i < d1.first; i++) {
		for (int j = 0; j < d2.second; j++) {
			T val = T();
			for (int k = 0; k < d1.second; k++) {
				val += l[i][k] * r[k][j];
			}
			res[i][j] = val;
		}
	}
	return res;
}