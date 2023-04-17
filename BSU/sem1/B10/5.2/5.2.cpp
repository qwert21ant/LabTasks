#include <iostream>
#include "ins_sort.h"
#include "select_sort.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Размер массива (до 1000): ";
    cin >> n;

    for (int mode = 1; mode <= 3; mode++) {
        int a[1000];

        if (mode == 1) {
            for (int i = 0; i < n; i++)
                a[i] = i;
        }
        else if (mode == 2) {
            for (int i = 0; i < n; i++)
                a[i] = n - i - 1;
        }
        else {
            for (int i = 0; i < n; i++)
                a[i] = rand() % 100;
        }

        cout << "Исходный массив: " << endl;
        for (int i = 0; i < n; i++)
            cout << a[i] << " ";
        cout << endl << endl;

        int b[1000];
        for (int i = 0; i < n; i++) b[i] = a[i];

        int ncmp, nswp;
        ins_sort(a, n, ncmp, nswp);

        //cout << "Массив после сортировки бинарными вставками: " << endl;
        //for (int i = 0; i < n; i++) cout << a[i] << " ";
        //cout << endl;
        cout << "Бинарными вставками:" << endl << endl;
        cout << "Количество сравнений: " << ncmp << ", теоретически: " << int(n * (log2(n) - 1. / log(2))) << endl;
        cout << "Количество перемещений: " << nswp << ", теоретически: " << (n * n + 9 * n - 10) / 4 << endl << endl;

        select_sort(b, n, ncmp, nswp);

        //cout << "Массив после сортировки выбором: " << endl;
        //for (int i = 0; i < n; i++) cout << b[i] << " ";
        //cout << endl;
        cout << "Выбором:" << endl << endl;
        cout << "Количество сравнений: " << ncmp << ", теоретически: " << (n * n - n) / 2 << endl;
        cout << "Количество перемещений: " << nswp << ", теоретически: " << int(n * (log(n) + 0.577216)) << endl << endl;

    }

    return 0;
}