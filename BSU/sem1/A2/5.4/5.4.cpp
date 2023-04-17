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
    INIT_INITIALIZE = 4
};

void init_random(int arr[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = rand() % MAX_RAND_VALUE - MAX_RAND_VALUE / 2;
}

void init_console(int arr[MAX_SIZE][MAX_SIZE], int n) {
    cout << "Введите матрицу:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
}

void init_values(int arr[MAX_SIZE][MAX_SIZE], int& n) {
    n = STANDART_N;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = i * n + j;
}

void print_arr(int arr[MAX_SIZE][MAX_SIZE], int n) {
    cout << "Матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << setw(5) << arr[i][j] << " ";
        cout << endl;
    }
}

bool check(int arr[MAX_SIZE][MAX_SIZE], int n, int pos) {
    for (int i = 0; i < n; i++)
        if (arr[i][pos] % 2)
            return false;

    return true;
}

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
        cout << "Выберите режим ввода (1 - рандом, 2 - консоль, 3 - значения, 4 - инициализация): ";
        cin >> mode;
    }

    int n = MAX_SIZE;

    if (mode != 3 && mode != 4) {
        while (n >= MAX_SIZE) {
            cout << "Размер матрицы (до 100): ";
            cin >> n;
        }
    }

    int arr[MAX_SIZE][MAX_SIZE] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

    if (mode == INIT_RANDOM)
        init_random(arr, n);
    else if (mode == INIT_CONSOLE)
        init_console(arr, n);
    else if (mode == INIT_VALUES)
        init_values(arr, n);
    else if (mode == INIT_INITIALIZE)
        n = 3;

    print_arr(arr, n);

    cout << "Столбцы с чётными значениями: ";
    for (int i = 0; i < n; i++)
        if (check(arr, n, i))
            cout << i << " ";
    cout << endl;

    cout << "Столбцы с отриц значением на гл диагонали:" << endl;
    for (int i = 0; i < n; i++)
        if (arr[i][i] < 0)
            cout << "  " << i << " - " << sum(arr, n, i) << endl;

    return 0;
}