#include "header.h"

int input() {
	int n;
	cout << "Enter n: ";
	cin >> n;

	return n;
}

list<int> gen_list(int len) {
	len *= 2;

	list<int> list;
	for (int i = 0; i < len; i++)
		list.push_back(rand() % 10);

	return list;
}

void print(const list<int>& l) {
	for (int el : l)
		cout << el << " ";
	cout << endl;
}

int solve(const list<int>& l, int n) {
	auto l_it = l.begin();
	auto r_it = --l.end();

	int res = min(*l_it, *r_it);
	while (--n) {
		++l_it;
		--r_it;

		res = max(res, min(*l_it, *r_it));
	}
	return res;
}