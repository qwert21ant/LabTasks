#include "header.h"

int main() {
	srand(time(0));

	int n;
	cout << "Enter array size: ";
	cin >> n;

	Vector in(n);
	in.random(100);

	cout << "Input: " << in << endl;

	Vector out = solve(in);
	cout << "Output: " << out << endl;

	return 0;
}