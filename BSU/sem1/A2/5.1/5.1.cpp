#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

double func(double x) {
    return (1 / sqrt(x) + cos(pow(M_E, x)) + cos(x * x)) /
        cbrt(log(pow(1 + x, 2)) + sqrt(pow(M_E, cos(x)) + pow(sin(M_PI * x), 2)));
}

double input() {
    double num = 0;
    cout << "Введите число: ";
    cin >> num;
    return num;
}

void output(double res) {
    cout << "Результат: " << res << endl;
}

int main() {
    setlocale(LC_ALL, "rus");

    double num = input();
    double res = func(num);

    output(res);

    return 0;
}