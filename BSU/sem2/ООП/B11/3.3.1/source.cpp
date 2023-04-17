#include "header.h"

void input(string& s1, string& s2, string& s3) {
	cout << "Enter L: ";
	cin >> s1;

	cout << "Enter L1: ";
	cin >> s2;

	cout << "Enter L2: ";
	cin >> s3;
}

template <class T>
T get_prev(T begin, T it) {
	T res = begin;
	T next = res;
	next++;

	while (next != it)
		res = next++;

	return res;
}

void solve(List& l, const List& l1, int l1_len, const List& l2, int l2_len) {
	auto l1_beg = ++l1.begin();
	auto l2_beg = ++l2.begin();

	for (auto it = ++l.begin(); ;) {
		it = search(it, l.end(), l1_beg, l1.end());
		if (it == l.end())
			break;

		it = get_prev(l.begin(), it);

		auto it_last = it;
		advance(it_last, l1_len + 1);

		l.erase_after(it, it_last);
		it = l.insert_after(it, l2_beg, l2.end());
	}
}

List list_from_string(const string& str) {
	List l;

	if (str.empty()) {
		l.push_front(0);
		return l;
	}

	for (int i = str.size() - 1; i >= 0; i--)
		l.push_front(str[i]);

	l.push_front(0);
	return l;
}

string string_from_list(const List& list) {
	string res;
	for (auto it = ++list.begin(); it != list.end(); ++it)
		res += *it;

	return res;
}