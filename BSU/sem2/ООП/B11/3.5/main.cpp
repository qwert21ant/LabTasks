#include "header.h"

int main() {
	string fname;
	cout << "Enter input file name: ";
	cin >> fname;

	ifstream fin(fname);

	if (!fin.is_open()) {
		cout << "Unable to open file" << endl;
		return 0;
	}

	auto res = get_cycles(fin);

	sort(res.begin(), res.end(), [](auto a, auto b) {
		return a.beginInd < b.beginInd;
	});

	for (auto el : res) {
		cout << el << endl;
	}

	return 0;
}