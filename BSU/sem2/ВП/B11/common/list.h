#pragma once

#include <iostream>
#include <iterator>
using namespace std;

template <class T>
class List {
private:
	class Node {
	public:
		~Node() = default;

		T& operator *() { return el; }
		const T& operator *() const { return el; }

		friend class List<T>;

	private:
		Node(T el, Node* prev = nullptr, Node* next = nullptr) : el(el), prev(prev), next(next) {};

		T el;
		Node* prev;
		Node* next;
	};

	template <class U>
	struct raw_iterator : std::iterator<bidirectional_iterator_tag, U> {
	public:
		raw_iterator(const raw_iterator& it) : node(it.node) {}
		~raw_iterator() {}

		U& operator *() { return **node; }
		const U& operator *() const { return **node; }

		raw_iterator& operator++() { next(); return *this; }
		raw_iterator operator++(int) { raw_iterator it(*this); next(); return it; }

		raw_iterator& operator--() { prev(); return *this; }
		raw_iterator operator--(int) { raw_iterator it(*this); prev(); return it; }

		bool operator ==(const raw_iterator& it) const { return node == it.node; }
		bool operator !=(const raw_iterator& it) const { return node != it.node; }

		friend class List<T>;

	private:
		raw_iterator(Node* node) : node(node) {}

		void next() { node = node->next; }
		void prev() { node = node->prev; }

		Node* node;
	};

public:
	List() : beginNode(nullptr), endNode(nullptr) {
		beginNode = new Node(T());
		endNode = new Node(T());
		beginNode->next = endNode;
		endNode->prev = beginNode;
	};
	~List() {
		for (auto node = beginNode; node;) {
			auto next = node->next;
			delete node;
			node = next;
		}
	}

	List(List<T>&& l) noexcept {
		beginNode = nullptr; endNode = nullptr;
		swap(beginNode, l.beginNode);
		swap(endNode, l.endNode);
	}

	using iterator = raw_iterator<T>;
	using const_iterator = raw_iterator<const T>;
	using reverse_iterator = reverse_iterator<iterator>;

	size_t length() const {
		size_t res = 0;
		for (auto node = beginNode; node; node = node->next)
			res++;
		return res - 2;
	}

	bool empty() const {
		return endNode->prev == beginNode;
	}

	void push(T el) {
		Node* node = new Node(el, endNode->prev, endNode);
		endNode->prev->next = node;
		endNode->prev = node;
	}

	void pop() {
		if (endNode->prev == begin)
			return;

		Node* node = endNode->prev->prev;

		delete endNode->prev;
		node->next = endNode;
		endNode->prev = node;
	}

	iterator insert(iterator it, T val) {
		Node* node = new Node(val, it.node, it.node->next);

		it.node->next->prev = node;
		it.node->next = node;
		return iterator(node);
	}

	iterator erase(iterator it) {
		auto res = iterator(it.node->next);

		it.node->next->prev = it.node->prev;
		it.node->prev->next = it.node->next;
		delete it.node;

		return res;
	}

	iterator erase(iterator it, size_t count) {
		auto lastIt = it;
		advance(lastIt, count);
		it.node->prev->next = lastIt.node;
		lastIt.node->prev = it.node->prev;
		for (auto curIt = it; curIt != lastIt;) {
			auto next = curIt; next++;
			delete[] curIt.node;
			curIt = next;
		}
		return lastIt;
	}

	iterator begin() { return ++iterator(beginNode); }
	iterator end() { return iterator(endNode); }

	const_iterator begin() const { return ++const_iterator(beginNode); }
	const_iterator end() const { return const_iterator(endNode); }

	const_iterator cbegin() const { return ++const_iterator(beginNode); }
	const_iterator cend() const { return const_iterator(endNode); }

	reverse_iterator rbegin() { return ++reverse_iterator(endNode); }
	reverse_iterator rend() { return reverse_iterator(beginNode); }

private:
	Node* beginNode;
	Node* endNode;
};

template <class T>
void print(List<T>& list, string delim = " ") {
	for (const auto& val : list)
		cout << val << delim;
	cout << endl;
}