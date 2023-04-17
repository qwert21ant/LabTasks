#pragma once

#include <iostream>
#include <iomanip>

#include <fstream>
#include <vector>
#include "../json/json.h"

using namespace std;
using namespace Json;

struct Student {
	string name;
	bool male;
	int age;
	int course;
	double grade;
};

bool student_from_json(Student& student, JsonObject* json);
bool parse_students(JsonObject* json, vector<Student>& students, int& course);
JsonObject* solve(vector<Student>& students, int course);