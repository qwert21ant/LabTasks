#include "header.h"

int main() {
	Number num1, num2;
	string s;

	cout << "Enter first number: ";
	cin >> num1;

	cout << "Enter second number: ";
	cin >> num2;

	cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
	cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;

	Number num(100);

	num.from_int(5);

	cout << "5^100 = " << (num ^ 100) << endl;

	return 0;
}