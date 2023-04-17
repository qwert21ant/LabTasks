#include "header.h"

void random(vector<int>& v, int max_len) {
	for (int& a : v)
		a = rand() % max_len;
}

void print(const vector<int>& v) {
	for (int a : v)
		cout << a << " ";
	cout << endl;
}

vector<int> solve(const vector<int>& v) {
	vector<int> res;

	vector<bool> arr(10001, false);
	for (int i = 0; i < v.size(); i++)
		arr[v[i]] = true;

	for (int i = 0; i < 10001; i++)
		if (arr[i])
			res.push_back(i);

	return res;
}