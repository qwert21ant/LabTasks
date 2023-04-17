#pragma once

#include <iostream>
#include <vector>

using std::vector;

template <class T>
using Vector = std::vector<T>;

template <class T>
class Matrix;

template <class T, bool IsConst>
class MatrixProxy {
public:
	~MatrixProxy() = default;

	using return_type = std::conditional_t<IsConst, const T, T>;
	using vector_type = std::conditional_t<IsConst, const Vector<T>, Vector<T>>;

	return_type& operator[](size_t ind) {
		if (ind >= data.size())
			throw std::out_of_range("");

		return data[ind];
	}

	friend class Matrix<T>;

private:
	MatrixProxy(vector_type& data) : data(data) {};

	vector_type& data;
};

template <class T>
class Matrix {
public:
	Matrix(size_t n, size_t m, T value = T()) : n_(n), m_(m), data_(n, Vector<T>(m, value)), id_(counter_++) {
		//std::cout << "Constructor " << id_ << std::endl;
	};

	Matrix(const Matrix& mat) : n_(mat.n_), m_(mat.m_), data_(mat.data_), id_(counter_++) {
		//std::cout << "Copy cnstr " << id_ << " from " << mat.id_ << std::endl;
	};

	Matrix& operator =(const Matrix& mat) {
		//std::cout << "Copy oper " << id_ << " from " << mat.id_ << std::endl;

		n_ = mat.n_;
		m_ = mat.m_;
		data_ = mat.data_;

		return *this;
	};

	Matrix(Matrix&& mat) {
		n_ = mat.n_;
		m_ = mat.m_;
		data_ = std::move(mat.data_);
		id_ = counter_++;

		//std::cout << "Move cnstr " << id_ << " from " << mat.id_ << std::endl;
	};

	Matrix& operator =(Matrix&& mat) {
		//std::cout << "Move oper " << id_ << " from " << mat.id_ << std::endl;

		n_ = mat.n_;
		m_ = mat.m_;
		data_ = std::move(mat.data_);

		return *this;
	};

	size_t get_rows() const {
		return n_;
	};

	size_t get_cols() const {
		return m_;
	};

	/*static Matrix Identity(size_t size) {
		Matrix res(size, size, T());
		for (int i = 0; i < size; i++)
			res[i][i] = 1;
		return res;
	};*/

	MatrixProxy<T, false> operator [](size_t ind) {
		if (ind >= n_)
			throw std::out_of_range("");

		return MatrixProxy<T, false>(data_[ind]);
	}

	MatrixProxy<T, true> operator [](size_t ind) const {
		if (ind >= n_)
			throw std::out_of_range("");

		return MatrixProxy<T, true>(data_[ind]);
	}

	friend Matrix operator *(const Matrix& l, const Matrix& r) {
		if (l.m_ != r.n_)
			throw std::exception("Wrong operands");

		Matrix<T> res(l.n_, r.m_);

		for (int i = 0; i < l.n_; i++) {
			for (int j = 0; j < r.m_; j++) {
				T val = T();
				for (int k = 0; k < l.m_; k++)
					val += l.data_[i][k] * r.data_[k][j];

				res.data_[i][j] = val;
			}
		}

		return res;
	};

	friend Matrix operator ^(const Matrix& mat, int s) {
		if (mat.n_ != mat.m_)
			throw std::exception("Wrong operands");

		if (s == 0)
			throw std::exception("Wrong operands");

		Matrix<T> res = mat;

		for (int i = 0; i < s - 1; i++)
			res = res * mat;

		return res;
	};

	friend std::ostream& operator <<(std::ostream& out, const Matrix& mat) {
		out << "Matrix " << mat.id_ << ":" << std::endl;
		for (int i = 0; i < mat.n_; i++) {
			for (int j = 0; j < mat.m_; j++)
				out << mat.data_[i][j] << " ";
			out << std::endl;
		}

		return out;
	};

	~Matrix() = default;

private:
	size_t n_, m_;
	vector<vector<T>> data_;

	int id_;

	static int counter_;
};

template <class T>
int Matrix<T>::counter_ = 1;