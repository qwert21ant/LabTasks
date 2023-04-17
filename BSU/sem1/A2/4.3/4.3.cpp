#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

const char delim[] = " .,:;!?-()";

int main() {
    setlocale(LC_ALL, "rus");

    char in[3000]{}, out[3000]{};

    cout << "Введите строку: ";
    cin.getline(in, 1000);

    int posOut = 0;
    char* word = strtok(in, delim);
    do {
        if (word[0] == 'a') {
            strcpy(out + posOut, word);
            posOut += strlen(word);
            out[posOut++] = ' ';
            out[posOut] = '\0';
        }
    } while ((word = strtok(nullptr, delim)) != nullptr);

    cout << "Результат: " << out << endl;

    return 0;
}