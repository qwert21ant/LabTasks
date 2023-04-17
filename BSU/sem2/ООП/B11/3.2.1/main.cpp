#include "header.h"

int main() {
	srand(time(0));

	int n;
	cout << "Enter array size: ";
	cin >> n;

	vector<int> in(n);
	random(in, 100);

	cout << "Input: ";
	print(in);

	vector<int> out = solve(in);
	cout << "Output: ";
	print(out);

	return 0;
}