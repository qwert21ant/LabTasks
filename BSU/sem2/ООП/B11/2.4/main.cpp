#include "header.h"

int main() {
	String s1, s2;
	input(s1, s2);

	cout << "First string exclude second: " << exclude(s1, s2) << endl;

	cout << boolalpha;
	cout << "Is first string a palindrome: " << bool(s1) << endl;
	cout << "Is second string a palindrome: " << bool(s2) << endl;
	return 0;
}