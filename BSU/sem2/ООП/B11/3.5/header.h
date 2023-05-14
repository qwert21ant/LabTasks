#pragma once

#include <iostream>
#include <iomanip>

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

enum class CycleType {
	None = 0,
	Do,
	While,
	For
};

struct Cycle {
	CycleType type;
	int beginInd;
	int endInd;
};

ostream& operator <<(ostream&, const Cycle&);

vector<Cycle> get_cycles(istream&);