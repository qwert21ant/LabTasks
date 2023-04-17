#include "header.h"

string to_bin(int num) {
	string res;

	do {
		res.push_back('0' + (num & 1));
	} while (num >>= 1);

	reverse(res.begin(), res.end());

	return res;
}

int from_bin(string str) {
	int res = 0;

	for (int i = 0; i < str.length(); i++)
		res += (str[i] - '0') << (str.length() - i - 1);

	return res;
}