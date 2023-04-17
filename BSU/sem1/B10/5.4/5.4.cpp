#include <iostream>

using namespace std;

void func(char* str, int pos, int n) {
    if (pos + n >= strlen(str)) {
        str[pos] = 0;
        return;
    }

    int i = pos;
    for (; i + n <= strlen(str); i++) {
        str[i] = str[i + n];
    }
}

int main(){
    setlocale(LC_ALL, "rus");

    char str[1000];
    cout << "Введите строку: ";
    cin >> str;

    for (int i = 0; ; ) {
        int l = 0, r = 0;
        while (str[i] != '"' && str[i]) i++;
        if (!str[i] || !str[i+1]) break;
        l = ++i;
        while (str[i] != '"' && str[i]) i++;
        if (!str[i]) break;
        r = i - 1;

        func(str, l, r - l + 1);
        i = l + 1;
    }

    cout << str;

    return 0;
}