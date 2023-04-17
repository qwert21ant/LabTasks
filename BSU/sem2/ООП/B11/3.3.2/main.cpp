#include "header.h"

int main() {
	srand(time(0));

	int n = input();

	list<int> list = gen_list(n);

	cout << "Input: ";
	print(list);

	cout << "Result: " << solve(list, n) << endl;

	return 0;
}