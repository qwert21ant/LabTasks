#pragma once

#include <iostream>
#include <utility>

#include "../common/Task.h"

class TaskList {
public:
	TaskList();

	TaskList(const TaskList&);
	TaskList& operator =(const TaskList&);

	TaskList(TaskList&&);
	TaskList& operator =(TaskList&&);

	void push_front(Task*);
	void pop_front();

	void clear();

	~TaskList();

	friend std::ostream& operator <<(std::ostream&, const TaskList&);

private:
	struct Node {
		Task* value;
		Node* next;
	};

	Node* begin_;
};