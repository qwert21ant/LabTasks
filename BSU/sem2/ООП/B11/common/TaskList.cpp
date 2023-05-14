#include "TaskList.h"

using namespace std;
using namespace Json;

TaskList::TaskList() : size_(0), capacity_(0), data_(nullptr) {};

TaskList::TaskList(const TaskList& tl) : size_(tl.size_), capacity_(tl.size_), data_(nullptr) {
	data_ = new Task* [size_];
	for (int i = 0; i < size_; i++)
		data_[i] = tl.data_[i]->Clone();
}

TaskList& TaskList::operator =(const TaskList& tl) {
	if (this == &tl)
		return *this;

	this->~TaskList();

	size_ = tl.size_;
	capacity_ = size_;

	data_ = new Task* [size_];
	for (int i = 0; i < size_; i++)
		data_[i] = tl.data_[i]->Clone();

	return *this;
}

TaskList::TaskList(TaskList&& tl) noexcept : size_(tl.size_), capacity_(tl.capacity_), data_(tl.data_) {
	tl.size_ = 0;
	tl.capacity_ = 0;
	tl.data_ = nullptr;
}

TaskList& TaskList::operator =(TaskList&& tl) {
	if (this == &tl)
		return *this;

	this->~TaskList();

	size_ = tl.size_;
	capacity_ = tl.capacity_;
	data_ = tl.data_;

	tl.size_ = 0;
	tl.capacity_ = 0;
	tl.data_ = nullptr;

	return *this;
}

int TaskList::size() const { return size_; }

void TaskList::append(Task* task) {
	if (size_ == capacity_)
		resize((capacity_ + 1) * 2);

	data_[size_++] = task;
}

void TaskList::remove(int ind) {
	if (ind < 0 || ind >= size_)
		throw out_of_range("");

	delete data_[ind];
	for (int i = ind; i < size_ - 1; i++)
		data_[i] = data_[i + 1];
	size_--;
}

void TaskList::clear() {
	for (int i = 0; i < size_; i++)
		delete data_[i];
	size_ = 0;
}

void TaskList::resize(int new_size) {
	if (capacity_ >= new_size) return;

	capacity_ = new_size;

	Task** new_data = new Task* [new_size];
	for (int i = 0; i < size_; i++)
		new_data[i] = data_[i];

	delete[] data_;
	data_ = new_data;
}

TaskList::~TaskList() {
	clear();
	delete[] data_;
}

JsonObject* TaskList::toJSON() const {
	JsonObject* root = create_object();

	JsonObject* tl = create_array();

	for (int i = 0; i < size_; i++)
		add_field(tl, "", data_[i]->ToJSON());

	add_field(root, "tasklist", tl);

	return root;
}

TaskList TaskList::fromJSON(JsonObject* json) {
	TaskList res;

	if (!Json::is_object(json))
		return res;

	JsonObject* tl = get_field(json, "tasklist");
	if (!Json::is_array(tl))
		return res;

	for (const JsonField& field : tl->fields) {
		JsonObject* jTask = field.value;

		if (!Json::is_object(jTask))
			continue;

		JsonObject* type = get_field(jTask, "type");

		if (!is_string(type))
			continue;

		Task* task = nullptr;

		string str_type = get_string(type);
		if (str_type == "MonsterKillCount")
			task = new TaskMonsterKillCount();
		else if (str_type == "MonsterKillUnique")
			task = new TaskMonsterKillUnique();
		else if (str_type == "Delivery")
			task = new TaskDelivery();
		else if (str_type == "Security")
			task = new TaskSecurity();
		else
			continue;

		task->FromJSON(jTask);

		res.append(task);
	}

	return res;
}

ostream& operator<<(ostream& out, const TaskList& tl) {
	for (int i = 0; i < tl.size_; i++)
		out << *tl.data_[i] << endl << endl;
	
	return out;
}