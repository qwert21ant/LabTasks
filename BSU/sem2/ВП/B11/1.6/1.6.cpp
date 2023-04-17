#include "Header.h"

int main() {
    int n;
    cout << "Enter array length: ";
    cin >> n;

    int* data = new int[n];
    gen_rand(data, n);

    cout << "Int array: ";
    output(data, n);

    merge_sort(data, n);

    cout << "Sorted int array: ";
    output(data, n);

    delete[] data;

    double* data2 = new double[n];
    gen_rand(data2, n);

    cout << "Double array: ";
    output(data2, n);

    merge_sort(data2, n);

    cout << "Sorted double array: ";
    output(data2, n);

    delete[] data2;

    char** data3 = new char*[n];
    gen_rand(data3, n);

    cout << "String array: ";
    output(data3, n);

    merge_sort(data3, n);

    cout << "Sorted string array: ";
    output(data3, n);

    return 0;
}