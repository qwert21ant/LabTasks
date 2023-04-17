#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_RAND_VALUE = 100;
const int STANDART_N = 10;

enum {
    INIT_RANDOM = 1,
    INIT_CONSOLE = 2,
    INIT_VALUES = 3,
    INIT_INITIALIZATION = 4
};

int sum(int arr[MAX_SIZE][MAX_SIZE], int n, int pos) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i][pos];
    return sum;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int mode = 0;
    while (mode < 1 || mode > 4) {
        cout << "Выберите режим ввода (1 - рандом, 2 - консоль, 3 - значения, 4 - инициализация: ";
        cin >> mode;
    }

    int n = MAX_SIZE;

    if (mode != 3 && mode != 4) {
        while (n >= MAX_SIZE) {
            cout << "Размер матрицы (до 100): ";
            cin >> n;
        }
    }

    int arr[MAX_SIZE][MAX_SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    if (mode == INIT_RANDOM) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                arr[i][j] = rand() % MAX_RAND_VALUE - MAX_RAND_VALUE / 2;
    } else if (mode == INIT_CONSOLE) {
        cout << "Введите матрицу:" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> arr[i][j];
    } else if (mode == INIT_VALUES) {
        n = STANDART_N;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                arr[i][j] = i * n + j;
    } else if (mode == INIT_INITIALIZATION) {
        n = 3;
    }

    cout << "Матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(5) << arr[i][j] << " ";
        cout << endl;
    }

    cout << "Столбцы с чётными значениями: ";
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 0; j < n; j++)
            if (arr[j][i] % 2) {
                flag = false;
                break;
            }

        if (flag)
            cout << i << " ";
    }
    cout << endl;

    cout << "Столбцы с отриц значением на гл диагонали:" << endl;
    for (int i = 0; i < n; i++)
        if (arr[i][i] < 0) {
            int sum = 0;
            for (int j = 0; j < n; j++)
                sum += arr[j][i];

            cout << "  " << i << " - " << sum << endl;
        }

    return 0;
}
