#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int& get(int* A, int x, int y) {
    if (x > y) swap(x, y);

    return A[y * (y + 1) / 2 + x];
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int n;
    cout << "Размер матрицы: ";
    cin >> n;

    if (n * (n + 1) / 2 >= 1000) {
        cout << "Слишком большой размер матрицы" << endl;
        return 0;
    }

    int A[1000];
    int B[1000];

    for (int i = 0; i < n * (n + 1) / 2; i++) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }

    cout << "Матрица A:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setfill(' ') << setw(3) << get(A, i, j);
        }
        cout << endl;
    }

    cout << endl;
    cout << "Матрица B:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setfill(' ') << setw(3) << get(B, i, j);
        }
        cout << endl;
    }

    cout << endl;
    cout << "Матрица C:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = 0;
            for (int k = 0; k < n; k++)
                val += get(A, i, k) * get(B, k, j);

            cout << setfill(' ') << setw(4) << val;
        }
        cout << endl;
    }

    return 0;
}