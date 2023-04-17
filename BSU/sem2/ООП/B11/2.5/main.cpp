#include "header.h"

int main() {
	srand(time(0));

	int size;
	cout << "Enter number of elements: ";
	cin >> size;

	BinTree<int> tree = create_tree(size);

	cout << "Tree:" << endl;
	tree.print(cout);
	cout << endl;

	int n;
	cout << "Enter n: ";
	cin >> n;

	cout << "Answer: " << tree.solve(n) << endl;

	return 0;
}