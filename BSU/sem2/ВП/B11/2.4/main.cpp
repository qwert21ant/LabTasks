#include "header.h"

int main() {
	string str1, str2, str3;
	cout << "L: ";
	cin >> str1;
	cout << "L1: ";
	cin >> str2;
	cout << "L2: ";
	cin >> str3;

	List<char> s1 = from_string(str1);
	List<char> s2 = from_string(str2);
	List<char> s3 = from_string(str3);

	auto it = s1.begin();
	while(true) {
		it = search(it, s1.end(), s2.begin(), s2.end());
		
		if (it == s1.end())
			break;

		it = s1.erase(it, str2.length());
		--it;
		it = insert_list(s1, it, s3);
		++it;
	};

	cout << "Result: ";
	print(s1, "");

	return 0;
}