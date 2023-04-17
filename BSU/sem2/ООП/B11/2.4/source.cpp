#include "header.h"

void input(String& s1, String& s2) {
	cout << "Enter first string: ";
	cin >> s1;

	cout << "Enter second string: ";
	cin >> s2;
}

String exclude(const String& s1, const String& s2) {
	String res(s1);

	int prev_size = res.size();

	while (true) {
		res -= s2;
		if (res.size() == prev_size)
			break;

		prev_size = res.size();
	}

	return res;
}