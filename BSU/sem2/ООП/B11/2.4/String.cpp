#include "String.h"

String::String() {
	size_ = 0;
	data_ = new char[1];
	data_[0] = 0;
};

String::String(const char* str) {
	size_ = strlen(str);
	data_ = new char[size_ + 1];
	strcpy_s(data_, size_ + 1, str);
};

String::String(const String& str) {
	size_ = str.size_;
	data_ = new char[size_ + 1];
	strcpy_s(data_, size_ + 1, str.data_);
};

String& String::operator =(const String& str) {
	if (this == &str)
		return *this;

	this->~String();

	size_ = str.size_;
	data_ = new char[size_ + 1];
	strcpy_s(data_, size_ + 1, str.data_);
};

String::String(String&& str) noexcept {
	size_ = str.size_;
	data_ = str.data_;

	str.size_ = 0;
	str.data_ = nullptr;
};

String& String::operator =(String&& str) noexcept {
	std::swap(size_, str.size_);
	std::swap(data_, str.data_);

	return *this;
};

int String::size() const {
	return size_;
};

String& String::operator -=(const String& str) {
	char* pos = strstr(data_, str.data_);
	if (!pos)
		return *this;

	for (int i = 0; pos[i + str.size_]; i++)
		pos[i] = pos[i + str.size_];

	size_ -= str.size_;
	data_[size_] = 0;

	return *this;
};

String::operator bool() {
	for (int i = 0; i < size_ / 2; i++)
		if (data_[i] != data_[size_ - i - 1])
			return false;

	return true;
};

std::istream& operator >>(std::istream& in, String& str) {
	std::vector<char> tmp;

	char ch;
	while (isspace(ch = in.get()));
	do {
		tmp.push_back(ch);
	} while (!isspace(ch = in.get()));

	str.~String();
	str.size_ = tmp.size();
	str.data_ = new char[str.size_ + 1];

	strncpy_s(str.data_, str.size_ + 1, tmp.data(), str.size_);
	str.data_[str.size_] = 0;

	return in;
};

std::ostream& operator <<(std::ostream& out, const String& str) {
	return out << str.data_;
};

String::~String() {
	delete[] data_;
};