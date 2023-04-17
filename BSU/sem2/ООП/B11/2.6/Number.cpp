#include "Number.h"

Number::Number() {
	size_ = 8;
	data_ = Vector<uchar>(size_ / 2, 0);
};

Number::Number(size_t size) {
	size_ = size;
	data_ = Vector<uchar>((size_ + 1) / 2, 0);
};

size_t Number::size() const {
	return size_;
}

void Number::from_int(int num) {
	for (int i = 0; i < size_; i++, num >>= 4)
		set_digit(i, num & 0b1111);
}

uchar Number::operator [](size_t ind) const {
	if (ind >= size_)
		throw std::out_of_range("");

	if (ind % 2)
		return data_[ind / 2] >> 4;
	else
		return data_[ind / 2] & 0b1111;
}

Number& Number::operator +=(const Number& num) {
	int carry = 0;
	int size = std::min(data_.size(), num.data_.size());
	for (int i = 0; i < size; i++) {
		int value = int(data_[i]) + int(num.data_[i]) + carry;
		carry = value >> 8;
		value &= 0b11111111;
		data_[i] = value;
	}

	if (carry && size < data_.size()) {
		for (int i = size; i < data_.size(); i++) {
			int value = int(data_[i]) + carry;
			carry = value >> 8;
			value &= (1 << 8) - 1;
			data_[i] = value;
		}
	}

	return *this;
};

Number& Number::operator *=(const Number& num) {
	Vector<uchar> res(data_.size(), 0);

	int size = std::min(data_.size(), num.data_.size());

	for (int i = 0; i < data_.size(); i++) {
		int carry = 0;
		for (int j = 0; i + j < data_.size() && (j < num.data_.size() || carry); j++) {
			int prod = data_[i] * (j < num.data_.size() ? num.data_[j] : 0);
			int value = res[i + j] + prod + carry;
			res[i + j] = value & 0b11111111;
			carry = value >> 8;
		}
	}

	data_ = std::move(res);

	return *this;
};

Number& Number::operator ^=(int s) {
	Number tmp(*this);

	while (--s)
		*this *= tmp;

	return *this;
};

Number operator +(Number l, const Number& r) { return l += r; }
Number operator *(Number l, const Number& r) { return l *= r; }
Number operator ^(Number l, int s) { return l ^= s; }

bool ishex(char ch) {
	if ('0' <= ch && ch <= '9')
		return true;
	if ('a' <= ch && ch <= 'f')
		return true;
	if ('A' <= ch && ch <= 'F')
		return true;
	return false;
}

uchar tohex(char ch) {
	if ('0' <= ch && ch <= '9')
		return ch - '0';
	if ('a' <= ch && ch <= 'f')
		return ch - 'a' + 10;
	if ('A' <= ch && ch <= 'F')
		return ch - 'A' + 10;
	return -1;
}

char fromhex(uchar ch) {
	if (ch < 10)
		return '0' + ch;
	return 'a' + ch - 10;
}

void read_whitespace(std::istream& in) {
	char ch;
	ch = in.peek();

	while (in && isspace(ch))
		in.get(), ch = in.peek();
}

std::istream& operator >>(std::istream& in, Number& num) {
	read_whitespace(in);

	Vector<uchar> data;
	char ch = in.peek();
	while (ishex(ch)) {
		in.get();

		data.push_back(tohex(ch));

		ch = in.peek();
	}

	num.size_ = data.size();

	num.data_.resize((num.size_ + 1) / 2);
	for (int i = 0; i < data.size(); i += 2)
		num.data_[i / 2] = data[data.size() - 1 - i];
	for (int i = 1; i < data.size(); i += 2)
		num.data_[i / 2] |= data[data.size() - 1 - i] << 4;

	return in;
};

std::ostream& operator <<(std::ostream& out, const Number& num) {
	for (int i = num.size() - 1; i >= 0; i--) {
		if (!num[i] && i)
			continue;
		out << fromhex(num[i]);
	}

	return out;
};

void Number::set_digit(size_t ind, uchar value) {
	if (ind >= size_)
		return;

	if (ind & 1)
		data_[ind >> 1] = ((value & 0b1111) << 4) | (data_[ind >> 1] & 0b1111);
	else
		data_[ind >> 1] = ((data_[ind >> 1] >> 4) << 4) | (value & 0b1111);
}