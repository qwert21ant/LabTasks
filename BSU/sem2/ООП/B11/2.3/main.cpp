#include "header.h"

int main() {
	int n = input();

	List<int> list = gen_list(n);

	cout << "Input: ";
	list.print(cout);

	cout << "Result: " << list.solve(n) << endl;

	return 0;
}