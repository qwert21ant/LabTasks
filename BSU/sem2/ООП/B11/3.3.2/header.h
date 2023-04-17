#pragma once

#include <iostream>
#include <iomanip>

#include <list>

using namespace std;

int input();
list<int> gen_list(int len);
void print(const list<int>&);

int solve(const list<int>&, int);