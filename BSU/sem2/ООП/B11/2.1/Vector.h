#pragma once

#include <cstring>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>

class Vector {
 public:
	 Vector();
	 Vector(size_t);
	 Vector(size_t, int);
	 Vector(const std::initializer_list<int>&);

	 Vector(const Vector&);
	 Vector& operator =(const Vector&);

	 Vector(Vector&&);
	 Vector& operator =(Vector&&);

	 size_t size() const;
	 size_t capacity() const;

	 void reserve(size_t);
	 void resize(size_t);

	 void push_back(int);
	 void pop_back();

	 void random(int);

	 int& operator [](size_t);
	 const int& operator [](size_t) const;

	 friend std::ostream& operator <<(std::ostream&, const Vector&);

	 ~Vector();

 private:
	 int* data_;
	 size_t capacity_;
	 size_t size_;
};