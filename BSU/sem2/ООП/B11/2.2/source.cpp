#include "header.h"

void input(string& s1, string& s2, string& s3) {
	cout << "Enter L: ";
	cin >> s1;

	cout << "Enter L1: ";
	cin >> s2;

	cout << "Enter L2: ";
	cin >> s3;
}

void solve(List<char>& l, const List<char>& l1, int l1_len, const List<char>& l2, int l2_len) {
	for (int ind = 0; ;) {
		ind = l.find(l1, ind);
		if (ind == -1)
			break;

		l.remove(ind, l1_len);
		l.append(ind, l2);
		ind += l2_len;
	}
}

List<char> list_from_string(const string& str) {
	List<char> l;
	if (str.empty())
		return l;

	l.init(str.back());
	for (int i = str.size() - 2; i >= 0; i--)
		l.push_front(str[i]);
	return l;
}

std::string string_from_list(const List<char>& list) {
	string res;
	for (auto cur = list.begin_; cur; cur = cur->next)
		res += cur->value;
	
	return res;
}