#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> split(const string& s, const string& delim) {
    char* str = new char[s.length() + 1];
    strcpy(str, s.c_str());

    vector<string> res;
    char* word = strtok(str, delim.c_str());
    while (word) {
        res.push_back(word);
        word = strtok(nullptr, delim.c_str());
    }

    delete[] str;

    return res;
}

int countCh(const string& s) {
    int res = 0;
    int cur = 1;
    for (int i = 1; i < s.length(); i++) {
        if (s[i] == s[i - 1])
            cur++;
        else {
            res = max(res, cur);
            cur = 1;
        }
    }
    return max(res, cur);
}

bool comp(const string& a, const string& b) {
    return countCh(a) < countCh(b);
}

string join(const vector<string>& arr) {
    string res = "";
    for (const auto& str : arr)
        res += str + " ";
    return res;
}

int main() {
    setlocale(LC_ALL, "rus");

    string delim = " .,:;!?-()";

    cout << "Enter string:" << endl;

    string str;
    getline(cin, str);

    vector<string> words = split(str, delim);

    sort(words.begin(), words.end(), comp);

    cout << "Result: " << join(words) << endl;

    return 0;
}