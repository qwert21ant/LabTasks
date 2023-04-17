#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>

using namespace std;

enum MODE {
    STATIC = 1,
    RANDOM = 2,
    INPUT = 3
};

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int n;
    cout << "Размер матрицы (не больше 100): ";
    cin >> n;

    int A[100][100];
    int B[100][100];

    int mode;
    cout << "Выберите способ задания матрицы: встроенные значения(1), random(2), input(3): ";
    cin >> mode;

    if (mode == MODE::STATIC) {
        cout << "Матрица A:" << endl;
        int val = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++, val++) {
                A[i][j] = val;
                cout << setw(4) << A[i][j];
            }
            cout << endl;
        }
    } else if (mode == MODE::RANDOM) {
        cout << "Матрица A:" << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 100;
                cout << setw(4) << A[i][j];
            }
            cout << endl;
        }
        cout << endl;
    } else if (mode == MODE::INPUT) {
        cout << "Введите элементы матрицы через пробел: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }

        cout << "Матрица A:" << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << A[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int el = A[i][j];
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (i + j < n) {
                        if (k >= i && l >= j && k + l < n)
                            el = el > A[k][l] ? el : A[k][l];
                    } else {
                        if (k <= i && l <= j && k + l >= n - 1)
                            el = el > A[k][l] ? el : A[k][l];
                    }
                }
            }
            B[i][j] = el;
        }
    }

    cout << "Матрица B:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(4) << B[i][j];

        cout << endl;
    }

    return 0;
}