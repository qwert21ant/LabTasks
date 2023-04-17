#include "Complex.h"

Complex::Complex() {
	re_ = 0;
	im_ = 0;
}

Complex::Complex(int re, int im) {
	re_ = re;
	im_ = im;
};

Complex Complex::Rand(int max_val) {
	return Complex(rand() % max_val, rand() % max_val);
};

int& Complex::Re() { return re_; };
const int& Complex::Re() const { return re_; };

int& Complex::Im() { return im_; };
const int& Complex::Im() const { return im_; };

Complex& Complex::operator +=(const Complex& c) {
	re_ += c.re_;
	im_ += c.im_;
	return *this;
};

Complex& Complex::operator -=(const Complex& c) {
	re_ -= c.re_;
	im_ -= c.im_;
	return *this;
};

Complex& Complex::operator *=(const Complex& c) {
	int a = re_, b = im_;
	re_ = a * c.re_ - b * c.im_;
	im_ = a * c.im_ + b * c.re_;
	return *this;
};

Complex operator +(Complex l, const Complex& r) { return l += r; }
Complex operator -(Complex l, const Complex& r) { return l -= r; }
Complex operator *(Complex l, const Complex& r) { return l *= r; }

std::ostream& operator <<(std::ostream& out, const Complex& c) {
	return out << std::setw(3) << c.re_ << " + " << std::setw(3) << c.im_ << "i";
}