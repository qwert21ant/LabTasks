#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

using namespace std;

bool is_square(int x) {
    int sq = sqrt(x);
    return sq * sq == x;
}

int& func(int* arr, int n) {
    int mni = -1;
    for (int i = 0; i < n; i++) {
        if (!is_square(arr[i]))
            continue;

        if (mni == -1 || arr[mni] > arr[i])
            mni = i;
    }

    if (mni != -1)
        return arr[mni];

    int mxi = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[mxi])
            mxi = i;
    }

    return arr[mxi];
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int n;
    cout << "Enter array length: ";
    cin >> n;

    int* arr = new int[n];

    int mode = -1;
    while (mode != 1 && mode != 2) {
        cout << "Input (1 - random, 2 - console): ";
        cin >> mode;
    }

    if (mode == 1) {
        int max_val = 1000;
        cout << "Max value: ";
        cin >> max_val;

        for (int i = 0; i < n; i++)
            arr[i] = rand() % max_val;

        cout << "Array: ";
        for (int i = 0; i < n; i++)
            cout << setw(4) << arr[i] << " ";
        cout << endl;
    } else {
        cout << "Enter array: ";
        for (int i = 0; i < n; i++)
            cin >> arr[i];
    }

    int k;
    cout << "Enter k: ";
    cin >> k;

    func(arr, n) = k;

    cout << "Result: ";
    for (int i = 0; i < n; i++)
        cout << setw(4) << arr[i] << " ";

    delete[] arr;

    return 0;
}