#include "Task.h"
#include <sstream>

using namespace std;
using namespace Json;

Timestamp str_to_ts(string str) {
	istringstream ss(str);
	Timestamp ts;
	ss >> ts;
	return ts;
}

string ts_to_str(Timestamp ts) {
	char str[100];
	tm buf;
	gmtime_s(&buf, &ts);
	strftime(str, 100, "%F %T", &buf);

	return string(str);
}

string interval_to_str(Timestamp ts) {
	char str[100];

	int ss = ts % 60;
	ts /= 60;
	int mm = ts % 60;
	ts /= 60;
	int hh = ts % 24;
	ts /= 24;
	int dd = ts;

	if (dd == 1)
		sprintf_s(str, "1 day %02d:%02d:%02d", hh, mm, ss);
	else if (dd)
		sprintf_s(str, "%d days %02d:%02d:%02d", dd, hh, mm, ss);
	else
		sprintf_s(str, "%02d:%02d:%02d", hh, mm, ss);

	return string(str);
}

char* copy_str(const char* str) {
	if (!str) return nullptr;

	int len = strlen(str);
	
	char* res = new char[len + 1];
	strcpy_s(res, len + 1, str);

	return res;
}

Task::Task() : cost(0) {}
Task::Task(int cost) : cost(cost) {}

void Task::SetCost(int cost) { this->cost = cost; }
int Task::GetCost() const { return cost; }

void Task::Print(std::ostream& out) const {
	out << "| Cost: " << setw(30) << cost << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

JsonObject* Task::ToJSON() const {
	JsonObject* root = create_object();

	add_field(root, "type", create_string(""));
	add_field(root, "cost", create_number(cost));

	return root;
}

void Task::FromJSON(JsonObject* json) {
	JsonObject* field = get_field(json, "cost");
	if (is_number(field))
		cost = get_number(field);
}

ostream& operator <<(ostream& out, const Task& task) {
	task.Print(out);
	return out;
}


TaskMonsterKill::TaskMonsterKill() : description(nullptr), monster_id(1), location_id(1) {}
TaskMonsterKill::TaskMonsterKill(int cost, const char* desc, MonsterID mon_id, LocationID loc_id)
	: Task(cost) {
	SetDescription(desc);
	monster_id = mon_id;
	location_id = loc_id;
}

TaskMonsterKill::TaskMonsterKill(const TaskMonsterKill& task)
	: Task(task), description(copy_str(task.description)), monster_id(task.monster_id), location_id(task.location_id) {}

TaskMonsterKill& TaskMonsterKill::operator =(const TaskMonsterKill& task) {
	if (this == &task)
		return *this;

	(Task&)(*this) = (const Task&) task;

	delete[] description;

	description = copy_str(task.description);
	monster_id = task.monster_id;
	location_id = task.location_id;

	return *this;
}

TaskMonsterKill::TaskMonsterKill(TaskMonsterKill&& task) 
	: Task(move(task)), description(copy_str(task.description)), monster_id(task.monster_id), location_id(task.location_id) {
	task.description = nullptr;
	task.monster_id = 0;
	task.location_id = 0;
}

TaskMonsterKill& TaskMonsterKill::operator =(TaskMonsterKill&& task) {
	if (this == &task)
		return *this;

	(Task&)(*this) = (Task&&)(task);

	delete[] description;

	description = copy_str(task.description);
	monster_id = task.monster_id;
	location_id = task.location_id;

	task.description = nullptr;
	task.monster_id = 0;
	task.location_id = 0;

	return *this;
}

void TaskMonsterKill::SetDescription(const char* desc) {
	delete[] description;
	description = copy_str(desc);
}
const char* TaskMonsterKill::GetDescription() const { return description; }

void TaskMonsterKill::SetMonsterID(MonsterID mon_id) {
	if (mon_id < 1 || mon_id > MonsterIDMax)
		throw exception("Incorrect argument");

	monster_id = mon_id;
}
MonsterID TaskMonsterKill::GetMonsterID() const { return monster_id; }

void TaskMonsterKill::SetLocationID(LocationID loc_id) {
	if (loc_id < 1 || loc_id > LocationIDMax)
		throw exception("Incorrect argument");

	location_id = loc_id;
}
LocationID TaskMonsterKill::GetLocationID() const { return location_id; }

void TaskMonsterKill::Print(std::ostream& out) const {
	Task::Print(out);

	out << "| Description: " << setw(23) << description << " |" << endl;
	out << "| Monster: " << setw(27) << monster_id << " |" << endl;
	out << "| Location: " << setw(26) << location_id << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

JsonObject* TaskMonsterKill::ToJSON() const {
	JsonObject* root = Task::ToJSON();

	add_field(root, "description", create_string(description));
	add_field(root, "monster_id", create_number(monster_id));
	add_field(root, "location_id", create_number(location_id));

	return root;
}

void TaskMonsterKill::FromJSON(JsonObject* json) {
	Task::FromJSON(json);

	JsonObject* field = get_field(json, "description");
	if (is_string(field))
		SetDescription(get_string(field).c_str());

	field = get_field(json, "monster_id");
	if (is_number(field))
		monster_id = get_number(field);

	field = get_field(json, "location_id");
	if (is_number(field))
		location_id = get_number(field);
}

TaskMonsterKill::~TaskMonsterKill() { delete[] description; }


TaskMonsterKillCount::TaskMonsterKillCount() : amount(1) {}
TaskMonsterKillCount::TaskMonsterKillCount(int cost, const char* desc, MonsterID mon_id, LocationID loc_id, int amount)
	: TaskMonsterKill(cost, desc, mon_id, loc_id) {
	this->amount = amount;
}

void TaskMonsterKillCount::SetAmount(int amount) {
	if (amount < 1)
		throw exception("Incorrect argument");

	this->amount = amount;
}
int TaskMonsterKillCount::GetAmount() const { return amount; }

void TaskMonsterKillCount::Print(ostream& out) const {
	out << "*--------------------------------------*" << endl;
	out << "| Type: " << setw(30) << "MonsterKillCount" << " |" << endl;

	TaskMonsterKill::Print(out);
	
	out << "| Amount: " << setw(28) << amount << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

Task* TaskMonsterKillCount::Clone() const { return new TaskMonsterKillCount(*this); }

JsonObject* TaskMonsterKillCount::ToJSON() const {
	JsonObject* root = TaskMonsterKill::ToJSON();

	get_field(root, "type")->value = "MonsterKillCount";
	add_field(root, "amount", create_number(amount));

	return root;
}

void TaskMonsterKillCount::FromJSON(JsonObject* json) {
	TaskMonsterKill::FromJSON(json);

	JsonObject* field = get_field(json, "amount");
	if (is_number(field))
		amount = get_number(field);
}


TaskMonsterKillUnique::TaskMonsterKillUnique() : title(nullptr) {}
TaskMonsterKillUnique::TaskMonsterKillUnique(int cost, const char* desc, MonsterID mon_id, LocationID loc_id, const char* title)
	: TaskMonsterKill(cost, desc, mon_id, loc_id) {
	SetTitle(title);
}

TaskMonsterKillUnique::TaskMonsterKillUnique(const TaskMonsterKillUnique& task)
	: TaskMonsterKill(task), title(copy_str(task.title)) {}

TaskMonsterKillUnique& TaskMonsterKillUnique::operator =(const TaskMonsterKillUnique& task) {
	if (this == &task)
		return *this;
	
	(TaskMonsterKill&)(*this) = (const TaskMonsterKill&) task;

	delete[] title;

	title = copy_str(task.title);

	return *this;
}

TaskMonsterKillUnique::TaskMonsterKillUnique(TaskMonsterKillUnique&& task) 
	: TaskMonsterKill(move(task)) {
	title = task.title;
	task.title = nullptr;
}

TaskMonsterKillUnique& TaskMonsterKillUnique::operator =(TaskMonsterKillUnique&& task) {
	if (this == &task)
		return *this;

	(TaskMonsterKill&)(*this) = (TaskMonsterKill&&)(task);

	delete[] title;

	title = copy_str(task.title);
	task.title = nullptr;

	return *this;
}

void TaskMonsterKillUnique::SetTitle(const char* title) {
	delete[] this->title;

	int len = strlen(title);
	this->title = new char[len + 1];
	strcpy_s(this->title, len + 1, title);
}
const char* TaskMonsterKillUnique::GetTitle() const { return title; }

void TaskMonsterKillUnique::Print(ostream& out) const {
	out << "*--------------------------------------*" << endl;
	out << "| Type: " << setw(30) << "MonsterKillUnique" << " |" << endl;

	TaskMonsterKill::Print(out);

	out << "| Title: " << setw(29) << title << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

Task* TaskMonsterKillUnique::Clone() const { return new TaskMonsterKillUnique(*this); }

JsonObject* TaskMonsterKillUnique::ToJSON() const {
	JsonObject* root = TaskMonsterKill::ToJSON();

	get_field(root, "type")->value = "MonsterKillUnique";
	add_field(root, "title", create_string(title));

	return root;
}

void TaskMonsterKillUnique::FromJSON(JsonObject* json) {
	TaskMonsterKill::FromJSON(json);

	JsonObject* field = get_field(json, "title");
	if (is_string(field))
		SetTitle(get_string(field).c_str());
}

TaskMonsterKillUnique::~TaskMonsterKillUnique() { delete[] title; }


TaskTravel::TaskTravel() : begin_location_id(1), end_location_id(1), deadline(0) {}
TaskTravel::TaskTravel(int cost, LocationID beg_loc_id, LocationID end_loc_id, Timestamp deadline) : Task(cost) {
	if (beg_loc_id < 1 || beg_loc_id > LocationIDMax)
		throw exception("Incorrect argument");
	if (end_loc_id < 1 || end_loc_id > LocationIDMax)
		throw exception("Incorrect argument");

	begin_location_id = beg_loc_id;
	end_location_id = end_loc_id;
	this->deadline = deadline;
}

void TaskTravel::SetBeginLocationID(LocationID loc_id) {
	if (loc_id < 1 || loc_id > LocationIDMax)
		throw exception("Incorrect argument");

	begin_location_id = loc_id;
}
LocationID TaskTravel::GetBeginLocationID() const { return begin_location_id; }

void TaskTravel::SetEndLocationID(LocationID loc_id) {
	if (loc_id < 1 || loc_id > LocationIDMax)
		throw exception("Incorrect argument");

	end_location_id = loc_id;
}
LocationID TaskTravel::GetEndLocationID() const { return end_location_id; }

void TaskTravel::SetDeadline(Timestamp deadline) { this->deadline = deadline; }
Timestamp TaskTravel::GetDeadline() const { return deadline; }

void TaskTravel::Print(ostream& out) const {
	Task::Print(out);

	out << "| Begin location: " << setw(20) << begin_location_id << " |" << endl;
	out << "| End location: " << setw(22) << end_location_id << " |" << endl;
	out << "| Deadline: " << setw(26) << ts_to_str(deadline) << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

JsonObject* TaskTravel::ToJSON() const {
	JsonObject* root = Task::ToJSON();

	add_field(root, "begin_location_id", create_number(begin_location_id));
	add_field(root, "end_location_id", create_number(end_location_id));
	add_field(root, "deadline", create_string(to_string(deadline)));

	return root;
}

void TaskTravel::FromJSON(JsonObject* json) {
	Task::FromJSON(json);

	JsonObject* field = get_field(json, "begin_location_id");
	if (is_number(field))
		begin_location_id = get_number(field);

	field = get_field(json, "end_location_id");
	if (is_number(field))
		end_location_id = get_number(field);

	field = get_field(json, "deadline");
	if (is_string(field))
		deadline = str_to_ts(get_string(field));
}


TaskDelivery::TaskDelivery() : item_id(1) {}
TaskDelivery::TaskDelivery(int cost, LocationID beg_loc_id, LocationID end_loc_id, Timestamp deadline, ItemID item_id)
		: TaskTravel(cost, beg_loc_id, end_loc_id, deadline) {
	if (item_id < 1 || item_id > ItemIDMax)
		throw exception("Incorrect argument");

	this->item_id = item_id;
}

void TaskDelivery::SetItemID(ItemID item_id) {
	if (item_id < 1 || item_id > ItemIDMax)
		throw exception("Incorrect argument");

	this->item_id = item_id;
}
ItemID TaskDelivery::GetItemID() const { return item_id; }

void TaskDelivery::Print(ostream& out) const {
	out << "*--------------------------------------*" << endl;
	out << "| Type: " << setw(30) << "Delivery" << " |" << endl;

	TaskTravel::Print(out);
	
	out << "| Item: " << setw(30) << item_id << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

Task* TaskDelivery::Clone() const { return new TaskDelivery(*this); }

JsonObject* TaskDelivery::ToJSON() const {
	JsonObject* root = TaskTravel::ToJSON();

	get_field(root, "type")->value = "Delivery";
	add_field(root, "item_id", create_number(item_id));

	return root;
}

void TaskDelivery::FromJSON(JsonObject* json) {
	TaskTravel::FromJSON(json);

	JsonObject* field = get_field(json, "item_id");
	if (is_number(field))
		item_id = get_number(field);
}


TaskSecurity::TaskSecurity() : duration(0) {}
TaskSecurity::TaskSecurity(int cost, LocationID beg_loc_id, LocationID end_loc_id, Timestamp deadline, Timestamp duration)
		: TaskTravel(cost, beg_loc_id, end_loc_id, deadline) {
	this->duration = duration;
}

void TaskSecurity::SetDuration(Timestamp duration) { this->duration = duration; }
Timestamp TaskSecurity::GetDuration() const { return duration; }

void TaskSecurity::Print(ostream& out) const {
	out << "*--------------------------------------*" << endl;
	out << "| Type: " << setw(30) << "Security" << " |" << endl;

	TaskTravel::Print(out);

	out << "| Duration: " << setw(26) << interval_to_str(GetDuration()) << " |" << endl;
	out << "*--------------------------------------*" << endl;
}

Task* TaskSecurity::Clone() const { return new TaskSecurity(*this); }

JsonObject* TaskSecurity::ToJSON() const {
	JsonObject* root = TaskTravel::ToJSON();

	get_field(root, "type")->value = "Security";
	add_field(root, "duration", create_string(to_string(duration)));

	return root;
}

void TaskSecurity::FromJSON(JsonObject* json) {
	TaskTravel::FromJSON(json);

	JsonObject* field = get_field(json, "duration");
	if (is_string(field))
		duration = str_to_ts(get_string(field));
}




///




Timestamp current_time() {
	return chrono::system_clock::to_time_t(chrono::system_clock::now());
}

Timestamp get_hours(long long hh) {
	return hh * 3'600ll;
}

Task* gen_task() {
	int type = rand() % 4;

	Task* res = nullptr;

	if (type < 2) {
		TaskMonsterKill* tmp;

		if (type == 0) {
			TaskMonsterKillCount* task = new TaskMonsterKillCount();

			task->SetAmount(rand() % 20 + 1);

			tmp = task;
		}
		else {
			TaskMonsterKillUnique* task = new TaskMonsterKillUnique();

			char title[100] = "Title ";

			title[6] = 'A' + rand() % 26;
			title[7] = 0;

			task->SetTitle(title);

			tmp = task;
		}

		char desc[100] = "Description ";

		desc[12] = 'A' + rand() % 26;
		desc[13] = 0;

		tmp->SetDescription(desc);

		tmp->SetMonsterID(rand() % MonsterIDMax + 1);
		tmp->SetLocationID(rand() % LocationIDMax + 1);

		res = tmp;
	}
	else {
		TaskTravel* tmp;

		if (type == 2) {
			TaskDelivery* task = new TaskDelivery();

			task->SetItemID(rand() % ItemIDMax + 1);

			tmp = task;
		}
		else {
			TaskSecurity* task = new TaskSecurity();

			task->SetDuration(get_hours(rand() % 10 + 1));

			tmp = task;
		}

		tmp->SetBeginLocationID(rand() % LocationIDMax + 1);
		tmp->SetEndLocationID(rand() % LocationIDMax + 1);
		tmp->SetDeadline(current_time() + get_hours(rand() % 10 + 1));

		res = tmp;
	}

	res->SetCost(rand() % 1000 + 10);

	return res;
}