#include <iostream>

using namespace std;

int main(){
    setlocale(LC_ALL, "rus");

    int num;
    cout << "Введите число: ";
    cin >> num;

    char out[100];
    int ind = 0;

    do {
        out[ind++] = num & 1;
    } while (num >>= 1);

    cout << "Число в двоичной СС: ";

    while (ind--)
        cout << (out[ind] ? '1' : '0');

    return 0;
}