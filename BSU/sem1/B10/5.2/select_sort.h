#pragma once

#include <iostream>
using namespace std;

template <typename T>
void select_sort(T* a, int len, int& ncmp, int& nswp) {
	ncmp = nswp = 0;
	for (int i = 0; i < len - 1; i++) {
		int mn = a[i];
		int imn = i;

		for (int j = i + 1; j < len; j++, ncmp++)
			if (a[j] < mn) {
				mn = a[j]; nswp++;
				imn = j;
			}

		a[imn] = a[i];
		nswp++;
		a[i] = mn;
		//cout << i <<":" << nswp << " ";
		//nswp = 0;
	}
	//cout << endl;
}