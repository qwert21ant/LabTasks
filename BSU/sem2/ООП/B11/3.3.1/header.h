#pragma once

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <forward_list>

using namespace std;

using List = forward_list<char>;

void input(string& s1, string& s2, string& s3);

void solve(List& l, const List& l1, int l1_len, const List& l2, int l2_len);

List list_from_string(const string& str);
string string_from_list(const List& list);