#include "header.h"

void input(List& l, List& l1, List& l2) {
	string str, strL1, strL2;
	cout << "L: ";
	cin >> str;
	cout << "L1: ";
	cin >> strL1;
	cout << "L2: ";
	cin >> strL2;

	l1 = init_list(strL1.length());
	push_string(l1, strL1);

	l2 = init_list(strL2.length());
	push_string(l2, strL2);

	l = init_list(str.length() + (str.length() / strL1.length()) * (strL2.length() + 1) + 10);
	push_string(l, str);
}

List init_list(int len) {
	List list;
	list.capacity = len + 1;
	list.data = new char[list.capacity];
	list.next = new int[list.capacity];

	list.begin = 0;
	list.dataEnd = list.end = 1;

	list.len = 0;

	for (int i = 0; i < list.capacity - 1; i++) {
		list.data[i] = '.';
		list.next[i] = i + 1;
	}
	list.next[list.capacity - 1] = -1;
	return list;
}

void push_string(List& list, string s) {
	for (char ch : s) {
		list.data[list.end] = ch;
		list.dataEnd = list.end = list.next[list.end];
	}
	list.len += s.length();
}

void remove_substr(List& list, int pos, int len) {
	list.len -= len;
	int nextPos = list.next[pos];
	while (len-- && nextPos != list.end)
		nextPos = list.next[nextPos];
	list.next[pos] = nextPos;
	list.len += len;
}

int find_substr(List& list, int from, List& sub) {
	if (from == list.end)
		return -1;

	int l = sub.len;
	for (int pi = from, i = list.next[from]; i != list.end; pi = i, i = list.next[i]) {
		bool f = 0;
		int cnt = 0;
		for (int j = i, k = sub.next[sub.begin];
			j != list.end && k != sub.end;
			j = list.next[j], k = sub.next[k], cnt++) {
			if (list.data[j] != sub.data[k]) {
				f = 1;
				break;
			}
		}

		if (f || cnt != l)
			continue;

		return pi;
	}
	return -1;
}

int insert_list(List& list, int pos, List& sub) {
	int saved = list.dataEnd = list.next[list.dataEnd];
	int prev;
	for (int i = sub.next[sub.begin]; i != sub.end; i = sub.next[i]) {
		list.data[list.dataEnd] = sub.data[i];
		prev = list.dataEnd;
		list.dataEnd = list.next[list.dataEnd];
	}

	list.next[prev] = list.next[pos];
	list.next[pos] = saved;
	list.len += sub.len;
	return prev;
}

void replace(List& l, List& l1, List& l2) {
	for (int i = l.begin; ; ) {
		int pos = find_substr(l, i, l1);

		if (pos == -1)
			break;

		remove_substr(l, pos, l1.len);

		i = insert_list(l, pos, l2);
	}
}

void print_list(List& list) {
	for (int ci = list.next[list.begin]; ci != list.end; ci = list.next[ci]) {
		cout << list.data[ci];
	}
	cout << endl;
}

void dbg(List& list) {
	for (int i = 0; i < list.len; i++) {
		cout << setw(4) << list.data[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < list.len; i++)
		cout << setw(4) << list.next[i] << " ";
	cout << endl;
}