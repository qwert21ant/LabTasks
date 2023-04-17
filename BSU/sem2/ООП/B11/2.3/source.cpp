#include "header.h"

int input() {
	int n;
	cout << "Enter array length: ";
	cin >> n;

	return n;
}

List<int> gen_list(int len) {
	len *= 2;

	List<int> list;
	for (int i = 0; i < len; i++)
		list.push_back(rand() % 10);

	return list;
}