#pragma once

#include <iomanip>

class Complex {
public:
	Complex() : re(0), im(0) {};
	Complex(int re, int im) : re(re), im(im) {};
	~Complex() = default;

	Complex(const Complex&) = default;
	Complex& operator =(const Complex&) = default;

	static Complex Rand(int max_val = 1000) {
		return Complex(rand() % max_val, rand() % max_val);
	}

	int& Re() { return re; }
	const int& Re() const { return re; }
	int& Im() { return im; }
	const int& Im() const { return im; }

	Complex& operator +=(const Complex& c) {
		re += c.re;
		im += c.im;
		return *this;
	}
	Complex& operator -=(const Complex& c) {
		re -= c.re;
		im -= c.im;
		return *this;
	}
	Complex& operator *=(const Complex& c) {
		int a = re, b = im;
		re = a * c.re - b * c.im;
		im = a * c.im + b * c.re;
		return *this;
	}

	friend ostream& operator <<(ostream&, const Complex&);

private:
	int re, im;
};

Complex operator +(Complex l, const Complex& r) { return l += r; }
Complex operator -(Complex l, const Complex& r) { return l -= r; }
Complex operator *(Complex l, const Complex& r) { return l *= r; }

ostream& operator <<(ostream& out, const Complex& c) {
	return out << setw(4) << c.re << " + " << setw(4) << c.im << "i";
}