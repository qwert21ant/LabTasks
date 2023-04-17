#include "header.h"

int main() {
	int m;
	cout << "Enter number: ";
	cin >> m;

	string bin_m = to_bin(m);

	cout << "Binary: " << bin_m << endl;

	reverse(bin_m.begin(), bin_m.end());

	int n = from_bin(bin_m);

	cout << "Answer: " << n << endl;
	cout << "Binary: " << to_bin(n) << endl;

	return 0;
}