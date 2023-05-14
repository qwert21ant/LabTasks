#include "TaskList.h"

TaskList::TaskList() : begin_(new Node{ nullptr, nullptr }) {}

TaskList::TaskList(const TaskList& list) : TaskList() {
	Node* this_prev = begin_;
	Node* list_cur = list.begin_->next;

	while (list_cur) {
		Node* node = new Node{ list_cur->value->Clone(), nullptr };
		this_prev->next = node;

		this_prev = this_prev->next;
		list_cur = list_cur->next;
	}
}

TaskList& TaskList::operator =(const TaskList& list) {
	if (this == &list)
		return *this;

	this->~TaskList();

	begin_ = new Node{ nullptr, nullptr };

	Node* this_prev = begin_;
	Node* list_cur = list.begin_->next;

	while (list_cur) {
		Node* node = new Node{ list_cur->value->Clone(), nullptr };
		this_prev->next = node;

		this_prev = this_prev->next;
		list_cur = list_cur->next;
	}

	return *this;
}

TaskList::TaskList(TaskList&& list) : begin_(list.begin_) {
	list.begin_ = nullptr;
}

TaskList& TaskList::operator =(TaskList&& list) {
	if (this == &list)
		return *this;

	this->~TaskList();

	begin_ = list.begin_;
	list.begin_ = nullptr;

	return *this;
}

void TaskList::push_front(Task* task) {
	begin_->next = new Node{ task, begin_->next };
}

void TaskList::pop_front() {
	Node* node = begin_->next;
	begin_->next = node->next;

	delete node->value;
	delete node;
}

void TaskList::clear() {
	if (!begin_)
		return;

	while (begin_->next)
		pop_front();
}

TaskList::~TaskList() {
	clear();
	delete begin_;
}

std::ostream& operator <<(std::ostream& out, const TaskList& list) {
	TaskList::Node* cur = list.begin_->next;

	while (cur) {
		out << *cur->value << "\n\n";

		cur = cur->next;
	}

	return out;
}