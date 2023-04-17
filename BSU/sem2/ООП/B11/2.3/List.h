#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>

template <class T>
class List {
public:
	List() {
		begin_ = new Node{};
		end_ = new Node{};

		begin_->prev = nullptr;
		begin_->next = end_;

		end_->prev = begin_;
		end_->next = nullptr;
	};

	List(const List& list) {
		begin_ = new Node{};
		begin_->prev = nullptr;

		Node* this_prev = begin_;
		Node* list_cur = list.begin_->next;
		while (list_cur) {
			Node* node = new Node{ list_cur->value, this_prev, nullptr };
			this_prev->next = node;
			this_prev = node;

			list_cur = list_cur->next;
		}
		end_ = this_prev;
	};

	List& operator =(const List& list) {
		if (this == &list)
			return *this;

		this->~List();

		begin_ = new Node;
		begin_->prev = nullptr;

		Node* this_prev = begin_;
		Node* list_cur = list.begin_->next;
		while (list_cur) {
			Node* node = new Node{ list_cur->value, this_prev, nullptr };
			this_prev->next = node;
			this_prev = node;

			list_cur = list_cur->next;
		}
		end_ = this_prev;

		return *this;
	};

	List(List&& list) {
		begin_ = list.begin_;
		end_ = list.end_;

		list.begin_ = nullptr;
		list.end_ = nullptr;
	};

	List& operator =(List&& list) {
		std::swap(begin_, list.begin_);
		std::swap(end_, list.end_);

		return *this;
	};

	void append(int ind, T value) {
		Node* cur = begin_->next;
		while (cur && ind--)
			cur = cur->next;

		if (!cur)
			throw std::out_of_range("");

		Node* prev = cur->prev;
		Node* new_node = new Node{ value, prev, cur };

		cur->prev = new_node;
		prev->next = new_node;
	};

	void push_front(T value) {
		Node* next = begin_->next;
		begin_->next = new Node{ value, begin_, next };
		next->prev = begin_->next;
	};

	void push_back(T value) {
		Node* prev = end_->prev;
		end_->prev = new Node{ value, prev, end_ };
		prev->next = end_->prev;
	};

	void remove(int ind) {
		Node* cur = begin_->next;
		while (cur != end_ && ind--)
			cur = cur->next;

		if (cur == end_)
			throw std::out_of_range("");

		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;

		delete cur;
	};

	int find(T value) const {
		int res = 0;
		for (Node* cur = begin_->next; cur != end_; cur = cur->next, res++)
			if (cur->value == value)
				return res;

		return -1;
	};

	void print(std::ostream& out, std::string delim = " ") const {
		for (Node* cur = begin_->next; cur != end_; cur = cur->next)
			out << cur->value << delim;
		out << std::endl;
	};

	void clear() {
		Node* cur = begin_->next;
		while (cur != end_) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}

		begin_->next = end_;
		end_->prev = begin_;
	};

	T solve(int n) const {
		if (begin_->next == end_)
			throw std::exception("Incorrect size");

		Node* left = begin_->next;
		Node* right = end_->prev;

		int res = std::min(left->value, right->value);

		while (--n) {
			left = left->next;
			right = right->prev;

			res = std::max(res, std::min(left->value, right->value));
		}

		return res;
	};

	~List() {
		Node* cur = begin_;
		while (cur) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}
	};

private:
	struct Node;

	Node* begin_;
	Node* end_;
};

template <class T>
struct List<T>::Node {
	T value;
	Node* prev;
	Node* next;
};