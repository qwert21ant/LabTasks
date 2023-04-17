// 2.1. ЦЕЛОЧИСЛЕННАЯ АРИФМЕТИКА. ПРИВЕДЕНИЕ ТИПОВ

#include <iostream>

using namespace std;

int main(){
    setlocale(LC_ALL, "rus");

    int n, k;

    cout << "n = ";
    cin >> n;

    cout << "k = ";
    cin >> k;

    int cnt = 0;
    for (int i = 0; i < 10; i++) {
        int t = n;
        int cur = 0;

        do {
            cur += t % 10 == i;
        } while (t /= 10);

        cnt += cur > 1 ? cur : 0;
    }

    cout << "Всего одинаковых цифр: " << cnt << endl;

    cout << "Ответ: " << (cnt > k ? "Да" : "Нет") << endl;

    return 0;
}