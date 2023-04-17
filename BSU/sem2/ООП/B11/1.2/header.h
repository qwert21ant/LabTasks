#pragma once

#include <iostream>
#include <iomanip>

#include <algorithm>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

enum MODE {
	MODE_GENERATE = 1,
	MODE_READ,
	MODE_SOLVE
};

int select();

void generate();
void read_files();
void solve();