#include <iostream>
#include <iomanip>

using namespace std;

void output(int** a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(4) << *(*(a + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void input(int** a, int& n, int& m) {
    cout << "Введите размеры матрицы: ";
    cin >> n >> m;

    int mode;
    cout << "Выберите способ задания матрицы: ввод(1), рандом(2), стандартные значения(3): ";
    cin >> mode;

    if (mode == 1) {
        cout << "Введите матрицу: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> *(*(a + i) + j);
            }
        }

    } else if(mode == 2){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                *(*(a + i) + j) = rand() % 100;

        cout << "Матрица:" << endl;
        output(a, n, m);
    } else {
        int c = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                *(*(a + i) + j) = c++;

        cout << "Матрица:" << endl;
        output(a, n, m);
    }
}

int find_min(int* a, int n) {
    int mn = *a;
    for (int i = 1; i < n; i++)
        mn = *(a+i) < mn ? *(a + i) : mn;
    return mn;
}

void sort(int** a, int n, int m) {
    for (int i = 1; i < n; i++) {
        int* x = *(a + i);
        int val = find_min(x, m);
        int l = 0;
        int r = i - 1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (val > find_min(*(a + m), n))
                r = m - 1;
            else
                l = m + 1;
        }

        for (int j = i - 1; j >= l; j--)
            *(a + j + 1) = *(a + j);

        *(a + l) = x;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int a[100][100];
    int n, m;

    int* x[100];
    for (int i = 0; i < 100; i++)
        *(x + i) = *(a + i);

    input(x, n, m);

    sort(x, n, m);

    cout << "Отсортированныя матрица: " << endl;
    output(x, n, m);

    return 0;
}