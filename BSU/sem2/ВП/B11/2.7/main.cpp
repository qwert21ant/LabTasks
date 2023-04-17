#include "header.h"

int main() {
	srand(time(0));

	int n = input();

	int* data = fill_arr(n);

	Node* root = create_tree(data, n);

	print_tree(root);

	solve(root);

	return 0;
}