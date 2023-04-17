#include "header.h"

#include <queue>

struct Node {
	int value;
	Node* left;
	Node* right;
};

int* fill_arr(int size) {
	int* data = new int[size];
	cout << "Array: ";
	for (int i = 0; i < size; i++) {
		data[i] = rand() % 100;
		cout << setw(3) << data[i] << " ";
	}
	cout << endl;
	return data;
}

int input() {
	int n;
	cout << "Enter the number of values: ";
	cin >> n;
	return n;
}

void create_root(Node*& root, int val) {
	root = new Node{ val, nullptr, nullptr };
}

void add_value(Node* root, int val) {
	Node* cur = root;
	Node* prev = nullptr;
	while (cur) {
		prev = cur;
		if (val < cur->value)
			cur = cur->left;
		else
			cur = cur->right;
	}

	cur = new Node{ val, nullptr, nullptr };
	if (val < prev->value)
		prev->left = cur;
	else
		prev->right = cur;
}

Node* create_tree(int* data, int size) {
	Node* root = nullptr;
	create_root(root, data[0]);
	for (int i = 1; i < size; i++)
		add_value(root, data[i]);
	return root;
}

int count_depth(Node* node) {
	if (!node)
		return 0;
	return max(count_depth(node->left), count_depth(node->right)) + 1;
}

void out_gap(int depth, int total_depth) {
	int cnt_el = (1 << (total_depth - depth)) - 1;
	int cnt = cnt_el * 6 + 1;
	if (depth == total_depth)
		cnt = 1;
	for (int i = 0; i < cnt; i++)
		cout << " ";
}

void out_off(int depth, int total_depth) {
	int cnt_el = (1 << (total_depth - depth - 1)) - 1;
	int cnt = 3 + cnt_el * 6;
	if (depth == total_depth)
		cnt = 0;
	if (depth + 1 == total_depth)
		cnt = 3;
	for (int i = 0; i < cnt; i++)
		cout << " ";
}

void print_tree(Node* root) {
	int total_depth = count_depth(root);

	queue<pair<Node*, int>> q;
	q.push(make_pair(root, 0));

	out_off(0, total_depth - 1);

	int pd = 0;
	while (!q.empty()) {
		auto x = q.front(); q.pop();
		Node* node = x.first;
		int depth = x.second;

		if (depth == total_depth)
			continue;

		if (pd != depth) {
			cout << endl;
			out_off(depth, total_depth - 1);
		}
		pd = depth;

		if (node)
			cout << "[" << setw(3) << node->value << "]";
		else
			cout << "     ";// << "[ . ]";
		out_gap(depth, total_depth - 1);

		q.push(make_pair(node ? node->left : nullptr, depth + 1));
		q.push(make_pair(node ? node->right : nullptr, depth + 1));
	}
	cout << endl;
}

int count_branches(Node* node, int depth) {
	if (!node)
		return 0;
	if (!depth)
		return 1;
	int res = 0;
	res += count_branches(node->left, depth - 1);
	res += count_branches(node->right, depth - 1);
	return res;
}

void solve(Node* root) {
	int d;
	cout << "Enter level: ";
	cin >> d;

	cout << "Answer: " << count_branches(root, d) << endl;
}