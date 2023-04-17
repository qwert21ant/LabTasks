#include <iostream>

using namespace std;

void clear_digits(const char* in, char* out) {
    for (int posIn = 0, posOut = 0; posIn <= strlen(in); posIn++) {
        if (isdigit(in[posIn]))
            continue;

        out[posOut++] = in[posIn];
    }
}

void erase_substr(char* str, int pos, int val) {
    for (int i = 0; pos + i < strlen(str); i++) {
        str[pos + i] = str[pos + val + i];
        if (!str[pos + i])
            break;
    }
}

void insert_substr(char* str1, int pos, const char* str2) {
    int slen = strlen(str2);
    for (int i = strlen(str1); i >= pos; i--)
        str1[i + slen] = str1[i];

    for (int i = 0; i < slen; i++)
        str1[pos + i] = str2[i];
}

void replace(char* inout, const char* str1, const char* str2) {
    char* val;
    int prev_pos = 0;
    while ((val = strstr(inout + prev_pos, str1)) != nullptr) {
        int pos = val - inout;
        erase_substr(inout, pos, strlen(str1));
        insert_substr(inout, pos, str2);
        prev_pos = pos + strlen(str2);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    char in[3000]{}, out[3000]{};

    cout << "Введите строку: ";
    cin.getline(in, 3000);

    int n = strlen(in);

    clear_digits(in, out);
    replace(out, "child", "children");

    cout << "Результат: " << out << endl;

    return 0;
}