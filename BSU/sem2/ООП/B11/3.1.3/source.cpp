#include "header.h"

vector<string> split(const string& str, const string& delim) {
	vector<string> res;

	string cur;
	for (char ch : str) {
		if (delim.find(ch) == string::npos)
			cur.push_back(ch);
		else if (!cur.empty()) {
			res.push_back(cur);
			cur.clear();
		}
	}

	if (!cur.empty())
		res.push_back(cur);

	return res;
}

string join(const vector<string>& words, const string& delim) {
	string res;

	for (const auto& str : words)
		res += str + delim;

	return res;
}

bool check(const string& str) {
	char chars[256];
	memset(chars, 0, 256);

	for (char ch : str)
		chars[(unsigned char) ch]++;

	for (int i = 0; i < 256; i++)
		if (chars[i] == 1)
			return false;

	return true;
}

vector<string> filter(const vector<string>& vec, function<bool(const string&)> pred) {
	vector<string> res;
	copy_if(vec.begin(), vec.end(), back_inserter(res), pred);
	return res;
}