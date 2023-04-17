#include "header.h"

BinTree<int> create_tree(int size) {
	BinTree<int> tree;
	tree.init(rand() % 30);

	for (int i = 1; i < size; i++)
		tree.append(rand() % 30);

	return tree;
}