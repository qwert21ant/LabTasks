#pragma once

#include "Task.h"
#include "json.h"

class TaskList {
public:
	TaskList();
	TaskList(const TaskList&);
	TaskList& operator =(const TaskList&);

	TaskList(TaskList&&) noexcept;
	TaskList& operator =(TaskList&&);

	int size() const;

	void append(Task*);
	void remove(int);

	void clear();

	~TaskList();

	Json::JsonObject* toJSON() const;
	static TaskList fromJSON(Json::JsonObject*);

	friend std::ostream& operator <<(std::ostream&, const TaskList&);

private:
	void resize(int);

	int size_;
	int capacity_;
	Task** data_;
};