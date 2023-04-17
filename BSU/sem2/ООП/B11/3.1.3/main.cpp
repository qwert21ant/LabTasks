#include "header.h"

int main() {
	string str;
	cout << "Enter string: ";
	getline(cin, str);

	auto words = split(str, " .,:;!?-()");

	words = filter(words, check);

	cout << "Answer: " << join(words, " ") << endl;

	return 0;
}