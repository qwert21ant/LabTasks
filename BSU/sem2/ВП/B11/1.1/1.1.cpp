#include <iostream>
#include <iomanip>

using namespace std;

int input() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    return n;
}

void output(int** mat, int n) {
    cout << "Matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void fillRect(int** mat, int n, int step) {
    int left = n / 2 - step;
    int right = n / 2 + step;

    int value = (2 * step - 1) * (2 * step - 1) + 1;

    for (int i = left + 1; i <= right; i++)
        mat[left][i] = value++;

    for (int i = left + 1; i <= right; i++)
        mat[i][right] = value++;

    for (int i = right - 1; i >= left; i--)
        mat[right][i] = value++;

    for (int i = right - 1; i >= left; i--)
        mat[i][left] = value++;
}

void fill(int** mat, int n) {
    mat[n / 2][n / 2] = 1;
    for (int i = 1; i <= n / 2; i++)
        fillRect(mat, n, i);
}

int main() {
    setlocale(LC_ALL, "rus");

    int n = input();

    int** mat = new int*[n];
    for (int i = 0; i < n; i++) {
        mat[i] = new int[n];
        memset(mat[i], 0, n * sizeof(int));
    }

    fill(mat, n);

    output(mat, n);

    return 0;
}