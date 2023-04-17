#include "header.h"

Vector solve(const Vector& v) {
	Vector res;

	Vector arr(10001);
	for (int i = 0; i < v.size(); i++)
		arr[v[i]]++;

	for (int i = 0; i < 10001; i++) {
		if (arr[i])
			res.push_back(i);
	}

	return res;
}