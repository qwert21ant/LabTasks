#pragma once

#include <cstring>
#include <iostream>
#include <vector>

class String {
public:
	String();
	String(const char*);

	String(const String&);
	String& operator =(const String&);

	String(String&&) noexcept;
	String& operator =(String&&) noexcept;

	int size() const;

	String& operator -=(const String&);
	operator bool();

	friend std::istream& operator >>(std::istream&, String&);
	friend std::ostream& operator <<(std::ostream&, const String&);

	~String();

private:
	int size_;
	char* data_;
};