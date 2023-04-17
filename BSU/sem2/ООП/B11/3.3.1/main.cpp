#include "header.h"

int main() {
	string s1, s2, s3;
	input(s1, s2, s3);

	List l = list_from_string(s1);
	List l1 = list_from_string(s2);
	List l2 = list_from_string(s3);

	solve(l, l1, s2.length(), l2, s3.length());

	cout << "Result: " << string_from_list(l) << endl;

	return 0;
}