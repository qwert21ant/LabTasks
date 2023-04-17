#pragma once
#include <iostream>
using namespace std;
template <typename T>
void ins_sort(T* a, int len, int& ncmp, int& nswp) {
	ncmp = nswp = 0;
	for (int i = 1; i < len; i++) {
		int x = a[i];
		int l = 0;
		int r = i - 1;

		while (l <= r) {
			int m = (l + r) / 2;
			ncmp++;
			if (x < a[m])
				r = m - 1;
			else
				l = m + 1;
		}

		for (int j = i - 1; j >= l; j--, nswp++)
			a[j + 1] = a[j];

		a[l] = x; nswp++;
		//cout << nswp << " ";
		//nswp = 0;
	}
	//cout << endl;
}