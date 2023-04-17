#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct List {
	char* data;
	int* next;
	int dataEnd;
	int capacity;

	int begin;
	int end;

	int len;
};

void input(List& l, List& l1, List& l2);

List init_list(int len);

void push_string(List& list, string s);

void remove_substr(List& list, int pos, int len);

int find_substr(List& list, int from, List& sub);

int insert_list(List& list, int pos, List& sub);

void replace(List& l, List& l1, List& l2);

void print_list(List&);

void dbg(List&);