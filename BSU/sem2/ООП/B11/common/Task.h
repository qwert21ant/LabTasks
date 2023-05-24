#pragma once

#include <iostream>
#include <iomanip>

#include <chrono>
#include <vector>

#include "json.h"

using uchar = unsigned char;

using MonsterID = unsigned short;
using LocationID = unsigned int;
using ItemID = unsigned short;
using Timestamp = time_t;

const MonsterID MonsterIDMax = 200;
const LocationID LocationIDMax = 1'000'000;
const ItemID ItemIDMax = 10'000;

class Task {
public:
	Task();
	Task(int);

	void SetCost(int);
	int GetCost() const;

	virtual void Print(std::ostream & = std::cout) const;
	virtual Task* Clone() const = 0;
	virtual Json::JsonObject* ToJSON() const;
	virtual void FromJSON(Json::JsonObject*);

	virtual ~Task() = default;

	friend std::ostream& operator <<(std::ostream&, const Task&);

private:
	int cost;
};

class TaskMonsterKill : public Task {
public:
	TaskMonsterKill();
	TaskMonsterKill(int, const char*, MonsterID, LocationID);

	TaskMonsterKill(const TaskMonsterKill&);
	TaskMonsterKill& operator =(const TaskMonsterKill&);

	TaskMonsterKill(TaskMonsterKill&&);
	TaskMonsterKill& operator =(TaskMonsterKill&&);

	void SetDescription(const char*);
	const char* GetDescription() const;

	void SetMonsterID(MonsterID);
	MonsterID GetMonsterID() const;

	void SetLocationID(LocationID);
	LocationID GetLocationID() const;

	virtual void Print(std::ostream & = std::cout) const override;
	virtual Task* Clone() const override = 0;
	virtual Json::JsonObject* ToJSON() const override;
	virtual void FromJSON(Json::JsonObject*) override;

	virtual ~TaskMonsterKill() override;

private:
	char* description;
	MonsterID monster_id;
	LocationID location_id;
};

class TaskMonsterKillCount : public TaskMonsterKill {
public:
	TaskMonsterKillCount();
	TaskMonsterKillCount(int, const char*, MonsterID, LocationID, int);

	TaskMonsterKillCount(const TaskMonsterKillCount&) = default;
	TaskMonsterKillCount& operator =(const TaskMonsterKillCount&) = default;

	TaskMonsterKillCount(TaskMonsterKillCount&&) = default;
	TaskMonsterKillCount& operator =(TaskMonsterKillCount&&) = default;

	void SetAmount(int);
	int GetAmount() const;

	void Print(std::ostream & = std::cout) const override;
	Task* Clone() const override;
	Json::JsonObject* ToJSON() const override;
	void FromJSON(Json::JsonObject*) override;

	~TaskMonsterKillCount() override = default;

private:
	int amount;
};

class TaskMonsterKillUnique : public TaskMonsterKill {
public:
	TaskMonsterKillUnique();
	TaskMonsterKillUnique(int, const char*, MonsterID, LocationID, const char*);

	TaskMonsterKillUnique(const TaskMonsterKillUnique&);
	TaskMonsterKillUnique& operator =(const TaskMonsterKillUnique&);

	TaskMonsterKillUnique(TaskMonsterKillUnique&&);
	TaskMonsterKillUnique& operator =(TaskMonsterKillUnique&&);

	void SetTitle(const char*);
	const char* GetTitle() const;

	void Print(std::ostream & = std::cout) const override;
	Task* Clone() const override;
	Json::JsonObject* ToJSON() const override;
	void FromJSON(Json::JsonObject*) override;

	~TaskMonsterKillUnique() override;

private:
	char* title;
};

class TaskTravel : public Task {
public:
	TaskTravel();
	TaskTravel(int, LocationID, LocationID, Timestamp);

	void SetBeginLocationID(LocationID);
	LocationID GetBeginLocationID() const;

	void SetEndLocationID(LocationID);
	LocationID GetEndLocationID() const;

	void SetDeadline(Timestamp);
	Timestamp GetDeadline() const;

	virtual void Print(std::ostream & = std::cout) const override;
	virtual Task* Clone() const override = 0;
	virtual Json::JsonObject* ToJSON() const override;
	virtual void FromJSON(Json::JsonObject*) override;

	~TaskTravel() override = default;

private:
	LocationID begin_location_id;
	LocationID end_location_id;
	Timestamp deadline;
};

class TaskDelivery : public TaskTravel {
public:
	TaskDelivery();
	TaskDelivery(int, LocationID, LocationID, Timestamp, ItemID);

	void SetItemID(ItemID);
	ItemID GetItemID() const;

	void Print(std::ostream & = std::cout) const override;
	Task* Clone() const override;
	Json::JsonObject* ToJSON() const override;
	void FromJSON(Json::JsonObject*) override;

	~TaskDelivery() override = default;

private:
	ItemID item_id;
};

class TaskSecurity : public TaskTravel {
public:
	TaskSecurity();
	TaskSecurity(int, LocationID, LocationID, Timestamp, Timestamp);

	void SetDuration(Timestamp);
	Timestamp GetDuration() const;

	void Print(std::ostream & = std::cout) const override;
	Task* Clone() const override;
	Json::JsonObject* ToJSON() const override;
	void FromJSON(Json::JsonObject*) override;

	~TaskSecurity() override = default;

private:
	Timestamp duration;
};

Task* gen_task();