#include "header.h"

int main() {
	string str;

	cout << "Enter string: ";
	cin >> str;

	if (is_int(str))
		cout << "It's int" << endl;
	else if (is_float(str))
		cout << "It's float" << endl;
	else
		cout << "It isn't number" << endl;

	return 0;
}