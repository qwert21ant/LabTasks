#pragma once

#include <iostream>

template <class T>
class BinTree {
public:
	BinTree() : root_(nullptr) {};

	BinTree(const BinTree& tree) {
		copy_node(root_, tree.root_);
	};

	BinTree& operator =(const BinTree& tree) {
		if (this == &tree)
			return *this;

		this->~BinTree();

		copy_node(root_, tree.root_);
	};

	BinTree(BinTree&& tree) {
		root_ = tree.root_;
		tree.root_ = nullptr;
	};

	BinTree& operator =(BinTree&& tree) {
		std::swap(root_, tree.root_);
		return *this;
	};

	void init(T value) {
		if(!root_)
			root_ = new Node{ value, nullptr, nullptr };
	};

	void append(T value) {
		append_node(root_, new Node{ value, nullptr, nullptr });
	};

	void remove(T value) {
		if (root_->value == value) {
			Node* tmp;

			if (root_->left) {
				tmp = root_->left;

				if (root_->right)
					append_node(root_->left, root_->right);
			} else {
				tmp = root_->right;

				if (root_->left)
					append_node(root_->right, root_->left);
			}

			delete root_;
			root_ = tmp;
		}

		Node* prev = root_;
		Node* cur = value < prev->value ? prev->left : prev->right;
		while (cur) {
			if (cur->value == value)
				break;

			prev = cur;
			cur = value < cur->value ? cur->left : cur->right;
		}

		if (!cur)
			return;

		remove_node(cur, prev);
	};

	bool find(T value) {
		Node* cur = root_;
		while (cur) {
			if (cur->value == value)
				return true;
			cur = value < cur->value ? cur->left : cur->right;
		}

		return false;
	};

	void print(std::ostream& out) {
		out << "[" << root_->value << "]" << std::endl;
		print_node(out, root_, "");
	};

	int solve(int n) {
		return count_branches(root_, n);
	};

	void clear() {
		remove_tree(root_);
		root_ = nullptr;
	};

	~BinTree() {
		remove_tree(root_);
	};

private:
	struct Node;

	int count_branches(Node* node, int depth) {
		if (!node)
			return 0;
		if (!depth)
			return 1;

		int res = 0;
		res += count_branches(node->left, depth - 1);
		res += count_branches(node->right, depth - 1);
		return res;
	};

	void remove_tree(Node* node) {
		if (!node)
			return;

		remove_tree(node->left);
		remove_tree(node->right);

		delete node;
	};

	void copy_node(Node* dst, Node* src) {
		if (!src)
			return;

		dst = new Node{ src->value };
		copy_node(dst->left, src->left);
		copy_node(dst->right, src->right);
	};

	void append_node(Node* dst, Node* src) {
		Node* prev = dst;
		Node* cur = src->value < prev->value ? prev->left : prev->right;
		while (cur) {
			prev = cur;
			cur = src->value < prev->value ? prev->left : prev->right;
		}

		(src->value < prev->value ? prev->left : prev->right) = src;
	};

	void remove_node(Node* node, Node* par) {
		Node*& ptr_to_change = par->left == node ? par->left : par->right;

		if (node->left) {
			ptr_to_change = node->left;

			if (node->right)
				append_node(node->left, node->right);
		}
		else {
			ptr_to_change = node->right;

			if (node->left)
				append_node(node->right, node->left);
		}

		delete node;
	};

	void print_node(std::ostream& out, Node* node, std::string filler) {
		if (!node)
			return;

		if (node->left) {
			out << filler << " │ " << std::endl;
			out << filler << " ├─[" << node->left->value << "]" << std::endl;
			print_node(out, node->left, filler + " │ ");
		}

		if (node->right) {
			out << filler << " │ " << std::endl;
			out << filler << " └─[" << node->right->value << "]" << std::endl;
			print_node(out, node->right, filler + "   ");
		}
	}

	Node* root_;
};

template <class T>
struct BinTree<T>::Node {
	T value;
	Node* left;
	Node* right;
};