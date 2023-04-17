#pragma once

#include <iostream>
#include <iomanip>

#include <fstream>
#include <vector>

using namespace std;

struct Student {
	string name;
	bool male;
	int age;
	int course;
	double grade;
};

void read_student(istream& in, Student& student);
void write_student(ostream& out, const Student& student);

void read_students(istream& in, vector<Student>& students);
void write_students(ostream& out, vector<Student>& students);

void solve(vector<Student>& students, int course, vector<Student>& result);