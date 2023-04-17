#pragma once

#include <iostream>
#include <utility>

template <class T>
class List {
public:
	List() : begin_(nullptr) {};

	List(int size, T value = T()) : begin_(nullptr) {
		init(value);
		size--;

		while (size--)
			push_front(value);
	};

	List(const List& list) : begin_(nullptr) {
		if (!list.begin_)
			return;

		init(list.begin_->value);

		Node* this_prev = begin_;
		Node* list_cur = list.begin_->next;
		while (list_cur) {
			Node* node = new Node{ list_cur->value, nullptr };
			this_prev->next = node;
			this_prev = node;
		}
	};

	List& operator =(const List& list) {
		if (this == &list)
			return;

		this->~List();
		begin_ = nullptr;

		if (!list.begin_)
			return *this;

		init(list.begin_->value);

		Node* this_prev = begin_;
		Node* list_cur = list.begin_->next;
		while (list_cur) {
			Node* node = new Node{ list_cur->value, nullptr };
			this_prev->next = node;
			this_prev = node;
		}

		return *this;
	};

	List(List&& list) {
		begin_ = list.begin_;
		list.begin_ = nullptr;
	};

	List& operator =(List&& list) {
		this->~List();

		begin_ = list.begin_;
		list.begin_ = nullptr;

		return *this;
	};

	void init(T value) {
		if (begin_)
			return;

		begin_ = new Node{ value, nullptr };
	};

	void append(int ind, T value) {
		if (!ind) {
			push_front(value);
			return;
		}

		Node* cur = begin_;
		while (cur && --ind)
			cur = cur->next;
		
		if (!cur)
			throw std::out_of_range("");

		cur->next = new Node{ value, cur->next };
	};

	void append(int ind, const List& list) {
		if (this == &list)
			return;

		if (!ind) {
			if (!list.begin_)
				return;

			Node* next = begin_;

			Node* cur = new Node{ list.begin_->value, nullptr };
			begin_ = cur;
			for (Node* cur_list = list.begin_->next; cur_list; cur_list = cur_list->next) {
				cur->next = new Node{ cur_list->value, nullptr };
				cur = cur->next;
			}

			cur->next = next;
			return;
		}

		Node* cur = begin_;
		while (cur && --ind)
			cur = cur->next;

		if (!cur)
			throw std::out_of_range("");

		Node* next = cur->next;

		for (Node* cur_list = list.begin_; cur_list; cur_list = cur_list->next) {
			cur->next = new Node{ cur_list->value, nullptr };
			cur = cur->next;
		}

		cur->next = next;
	};

	void push_front(T value) {
		begin_ = new Node{ value, begin_ };
	};

	void remove(int ind) {
		if (!ind) {
			Node* new_begin = begin_->next;
			delete begin_;
			begin_ = new_begin;
			return;
		}

		Node* prev = begin_;
		Node* cur = prev->next;
		while (cur && --ind) {
			prev = cur;
			cur = cur->next;
		}

		if (!cur)
			throw std::out_of_range("");

		prev->next = cur->next;
		delete cur;
	};

	void remove(int ind, int len) {
		if (!ind) {
			Node* new_begin = begin_;
			while (new_begin && len--) {
				Node* tmp = new_begin->next;
				delete new_begin;
				new_begin = tmp;
			}
			begin_ = new_begin;
			return;
		}

		Node* prev = begin_;
		Node* cur = prev->next;
		while (cur && --ind) {
			prev = cur;
			cur = cur->next;
		}

		if (!cur)
			throw std::out_of_range("");

		Node* next = cur;
		while (next && len--) {
			Node* tmp = next->next;
			delete next;
			next = tmp;
		}

		prev->next = next;
	};

	int find(T value, int from = 0) const {
		Node* cur = begin_;
		for (int tmp = from; cur && tmp; tmp--)
			cur = cur->next;

		if (!cur)
			return -1;

		for (int ind = 0; cur; cur = cur->next, ind++)
			if (cur->value == value)
				return from + ind;

		return -1;
	};

	int find(const List& list, int from = 0) const {
		Node* cur = begin_;
		for (int tmp = from; cur && tmp; tmp--)
			cur = cur->next;

		if (!cur)
			return -1;

		for (int ind = 0; cur; cur = cur->next, ind++) {
			if (cur->value != list.begin_->value)
				continue;

			Node* this_cur = cur->next;
			Node* list_cur = list.begin_->next;
			while (this_cur && list_cur && this_cur->value == list_cur->value) {
				this_cur = this_cur->next;
			  list_cur = list_cur->next;
			}

			if (list_cur)
				continue;

			return from + ind;
		}

		return -1;
	};

	void print(std::ostream& out, std::string delim = " ") const {
		for (Node* cur = begin_; cur; cur = cur->next)
			out << cur->value << delim;
		out << std::endl;
	};

	~List() {
		Node* cur = begin_;
		while (cur) {
			Node* next = cur->next;
			delete cur;
			cur = next;
		}
	}

	friend std::string string_from_list(const List<char>& list);

private:
	struct Node;

	Node* begin_;
};

template <class T>
struct List<T>::Node {
	T value;
	Node* next;
};