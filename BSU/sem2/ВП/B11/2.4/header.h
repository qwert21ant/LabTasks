#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "../common/list.h"

using namespace std;

List<char> from_string(const string& s) {
	List<char> res;

	for (auto& ch : s)
		res.push(ch);

	return res;
}

template <class T>
typename List<T>::iterator insert_list(List<T>& l, typename List<T>::iterator it, const List<T>& r) {
	for (auto val : r) {
		it = l.insert(it, val);
	}
	return it;
}