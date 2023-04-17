#pragma once

#include <iostream>
#include <iomanip>

class Complex {
public:
	Complex();
	Complex(int, int);

	Complex(const Complex&) = default;
	Complex& operator =(const Complex&) = default;

	Complex(Complex&&) = default;
	Complex& operator =(Complex&&) = default;

	static Complex Rand(int = 1000);

	int& Re();
	const int& Re() const;

	int& Im();
	const int& Im() const;

	Complex& operator +=(const Complex& c);
	Complex& operator -=(const Complex& c);
	Complex& operator *=(const Complex& c);

	friend Complex operator +(Complex l, const Complex& r);
	friend Complex operator -(Complex l, const Complex& r);
	friend Complex operator *(Complex l, const Complex& r);

	friend std::ostream& operator <<(std::ostream&, const Complex&);

	~Complex() = default;

private:
	int re_;
	int im_;
};