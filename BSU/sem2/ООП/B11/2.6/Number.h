#pragma once

#include "Vector.h"

#include <iostream>
#include <utility>

using uchar = unsigned char;

class Number {
public:
	Number();
	explicit Number(size_t);

	Number(const Number&) = default;
	Number& operator =(const Number&) = default;

	Number(Number&&) = default;
	Number& operator =(Number&&) = default;

	size_t size() const;

	void from_int(int);

	uchar operator[](size_t) const;

	Number& operator +=(const Number&);
	Number& operator *=(const Number&);
	Number& operator ^=(int);

	friend Number operator +(Number, const Number&);
	friend Number operator *(Number, const Number&);
	friend Number operator ^(Number, int);

	friend std::istream& operator >>(std::istream&, Number&);
	friend std::ostream& operator <<(std::ostream&, const Number&);

	~Number() = default;

private:
	void set_digit(size_t, uchar);

	Vector<uchar> data_;
	size_t size_;
};