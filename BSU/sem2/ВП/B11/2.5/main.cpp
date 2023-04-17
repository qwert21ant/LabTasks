#include "header.h"

int main() {
	List l, l1, l2;
	input(l, l1, l2);

	replace(l, l1, l2);

	cout << "Answer: ";
	print_list(l);

	return 0;
}