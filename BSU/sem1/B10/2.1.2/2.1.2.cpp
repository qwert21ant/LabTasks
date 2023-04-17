// 2.1. ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА. ПРИВЕДЕНИЕ ТИПОВ

#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    double n;
    int k;

    cout << "n = ";
    cin >> n;

    cout << "k = ";
    cin >> k;

    n *= 10;
    int D1 = int(n) % 10;

    bool flag = 0;
    for (int i = 1; i < k; i++) {
        n *= 10;
        int d = int(n) % 10;

        if (d != D1) {
            flag = 1;
            break;
        }

        //cout << d << endl;
    }

    cout << "Ответ: " << (flag ? "Нет" : "Да") << endl;

    return 0;
}