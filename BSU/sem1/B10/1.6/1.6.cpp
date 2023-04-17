// 1.6. ПОБИТОВЫЕ ОПЕРАЦИИ

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    unsigned long n;
    cout << "n = ";
    cin >> n;

    cout << n << endl;

    cout << "0 bit -  " << (n & 1) << endl;
    cout << "1 bit -  " << (n >> 1 & 1) << endl;
    cout << "15 bit - " << (n >> 15 & 1) << endl;

    n ^= 1 << 1 | 1 << 10;

    cout << "n = " << n << endl;

    system("pause");
    return 0;
}