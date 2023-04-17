#include <iostream>

using namespace std;

void to_bin(int num, char* out) {
    int ind = 0;
    do {
        out[ind++] = (num & 1) ? '1' : '0';
    } while (num >>= 1);
    out[ind] = '\0';
    _strrev(out);
}

int main() {
    setlocale(LC_ALL, "rus");

    int num;
    cout << "Введите число: ";
    cin >> num;

    char out[100];
    to_bin(num, out);

    cout << "Число в двоичной СС: " << out << endl;

    return 0;
}