#pragma once

#include <cstring>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <class T>
class Vector {
public:
	Vector() {
		data_ = nullptr;
		capacity_ = 0;
		size_ = 0;
	};

	Vector(size_t size) {
		data_ = new T[size];
		capacity_ = size;
		size_ = size;
	};

	Vector(size_t size, T value) {
		data_ = new T[size];
		for (int i = 0; i < size; i++)
			data_[i] = value;
		capacity_ = size;
		size_ = size;
	};

	Vector(const std::initializer_list<T>& list) {
		data_ = new T[list.size()];
		capacity_ = list.size();
		size_ = list.size();

		size_t ind = 0;
		for (const T& value : list)
			data_[ind++] = value;
	};

	Vector(const Vector& vec) {
		capacity_ = vec.capacity_;
		size_ = vec.size_;

		data_ = new T[size_];
		for (size_t i = 0; i < size_; i++)
			data_[i] = vec.data_[i];
	};

	Vector& operator =(const Vector& vec) {
		if (this == &vec)
			return *this;

		this->~Vector();

		capacity_ = vec.capacity_;
		size_ = vec.size_;

		data_ = new T[size_];
		for (size_t i = 0; i < size_; i++)
			data_[i] = vec.data_[i];

		return *this;
	};

	Vector(Vector&& vec) {
		data_ = vec.data_;
		capacity_ = vec.capacity_;
		size_ = vec.size_;

		vec.data_ = nullptr;
		vec.capacity_ = 0;
		vec.size_ = 0;
	};

	Vector& operator =(Vector&& vec) {
		this->~Vector();

		data_ = vec.data_;
		capacity_ = vec.capacity_;
		size_ = vec.size_;

		vec.data_ = nullptr;
		vec.capacity_ = 0;
		vec.size_ = 0;

		return *this;
	};

	size_t size() const {
		return size_;
	};

	size_t capacity() const {
		return capacity_;
	};

	void reserve(size_t capacity) {
		if (capacity <= capacity_)
			return;

		T* buf = new T[capacity];
		memcpy(buf, data_, sizeof(T) * size_);
		if (data_)
			delete[] data_;

		data_ = buf;
		capacity_ = capacity;
	};

	void resize(size_t size) {
		if (size <= capacity_) {
			size_ = size;
			return;
		}

		reserve(size);
		for (int i = size_; i < size; i++)
			new (&data_[i]) T();

		size_ = size;
	};

	void push_back(T value) {
		if (size_ == capacity_)
			reserve(capacity_ * 2 + 1);

		data_[size_++] = value;
	};

	void pop_back() {
		--size_;
	};

	T& operator [](size_t ind) {
		if (ind >= size_)
			throw std::out_of_range("");
		return data_[ind];
	};

	const T& operator [](size_t ind) const {
		if (ind >= size_)
			throw std::out_of_range("");
		return data_[ind];
	};

	friend std::ostream& operator <<(std::ostream& out, const Vector& vec) {
		for (int i = 0; i < vec.size(); i++)
			out << vec[i] << " ";
		return out;
	};

	~Vector() {
		delete[] data_;
	};

private:
	T* data_;
	size_t capacity_;
	size_t size_;
};