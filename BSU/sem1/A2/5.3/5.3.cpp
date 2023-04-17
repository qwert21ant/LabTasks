#include <iostream>
#include <ctime>

using namespace std;

int get_max(int arr[], int n) {
    int mx = arr[0];
    int mxi = 0;

    for (int i = 1; i < n; i++)
        if (arr[i] > mx) {
            mx = arr[i];
            mxi = i;
        }

    return mxi;
}

int get_sum(int arr[], int n) {
    int sum = 0;
    
    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum;
}

void init_random(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;
}

void init_console(int arr[], int n) {
    cout << "Введите массив: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void init_values(int arr[], int& n) {
    const int vals[10]{ 1, 2, 3, 4, 5, 6, 9, 4, 2, 3 };
    n = 10;
    for (int i = 0; i < n; i++)
        arr[i] = vals[i];
}

void print_arr(int arr[], int n) {
    cout << "Массив: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int mode = 0;
    while (mode < 1 || mode > 3) {
        cout << "Режим ввода (1 - рандом, 2 - консоль, 3 - значения): ";
        cin >> mode;
    }

    int n = 10000;

    if (mode != 3) {
        while (n >= 1000) {
            cout << "Размер массива (до 1000): ";
            cin >> n;
        }
    }
    
    int arr[1000]{};

    if (mode == 1)
        init_random(arr, n);
    else if (mode == 2)
        init_console(arr, n);
    else
        init_values(arr, n);

    print_arr(arr, n);

    int mxi = get_max(arr, n);
    int res = get_sum(arr, mxi);

    cout << "Рещультат: " << res << endl;

    return 0;
}