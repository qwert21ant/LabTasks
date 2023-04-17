#pragma once

#include <iostream>
#include <iomanip>

#include "List.h"

using namespace std;

void input(string& s1, string& s2, string& s3);

void solve(List<char>& l, const List<char>& l1, int l1_len, const List<char>& l2, int l2_len);

List<char> list_from_string(const string& str);
std::string string_from_list(const List<char>& list);