#include <iostream>

using namespace std;

const char str1[] = "child";
const int str1len = 5;

const char str2[] = "children";
const int str2len = 8;

int main() {
    setlocale(LC_ALL, "rus");
    char in[3000]{}, out[4000]{};

    cout << "Введите строку: ";
    cin.getline(in, 3000);

    int n = strlen(in);

    int posIn = 0, posOut = 0;
    for (; posIn < n; posIn++) {
        if (isdigit(in[posIn]))
            continue;

        int i = 0;
        while (in[posIn + i] == str1[i] && posIn + i < n)
            i++;

        if (i == str1len) {
            posIn += str1len - 1;
            for (int j = 0; j < str2len; j++, posOut++)
                out[posOut] = str2[j];
        } else {
            out[posOut++] = in[posIn];
        }
    }

    cout << "Результат: " << out << endl;

    return 0;
}