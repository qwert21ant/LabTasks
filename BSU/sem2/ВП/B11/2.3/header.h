#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../common/list.h"

using namespace std;

struct Student {
	string name;
	string date;
	int course;
	double grade;

	bool operator <(const Student& s) const {
		return name < s.name;
	}
};

ostream& operator <<(ostream& out, const Student& s) {
	return out << s.name << " [" << s.course << "] " << s.grade;
}

template <class T>
void add(List<T>& list, T val) {
	if (list.empty()) {
		list.push(val);
		return;
	}

	auto it = find_if(list.begin(), list.end(), [&val](const T& x) {
		return val < x;
	});

	if (it == list.end())
		list.push(val);
	else
		list.insert(--it, val);
}

double get_avg(const List<Student>& list, int course) {
	int cnt = 0;
	double sum = 0;
	for (auto& val : list) {
		if (val.course != course)
			continue;

		cnt++;
		sum += val.grade;
	}
	return sum / cnt;
}

List<Student> filter(List<Student>& list, int course, double grade) {
	List<Student> res;
	for (auto it = list.begin(); it != list.end();) {
		Student& el = *it;
		if (el.course != course || el.grade <= grade) {
			++it;
			continue;
		}
		
		add(res, el);
		it = list.erase(it);
	}

	return res;
}