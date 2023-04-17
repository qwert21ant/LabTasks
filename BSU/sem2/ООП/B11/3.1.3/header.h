#pragma once

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string&, const string&);
string join(const vector<string>&, const string&);
bool check(const string&);
vector<string> filter(const vector<string>&, function<bool(const string&)>);