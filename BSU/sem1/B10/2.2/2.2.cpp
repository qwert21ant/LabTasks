#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    double x0 = -0.5;
    double xn = 0.5;
    double dx = 0.1;

    const double EPS = 1e-6;

    for (double x = x0; x <= xn; x += dx) {
        double res = 1. + 0.5 * x;

        double power = -x * x;
        double numer = 1;
        double denom = 2 * 4;
        double delta = power * numer / denom;
        for (int i = 3, j = 6; abs(delta) >= EPS; i += 2, j += 2){
            //cout << delta << " ";
            res += delta;

            power *= -x;
            numer *= i;
            denom *= j;

            delta = power * numer / denom;
        }
        //cout << endl;

        cout << "f(" << x << ") = " << res << endl;
        cout << "Check - " << sqrt(1 + x) << endl;

        cout << "Сравнение: " << ((abs(sqrt(1 + x) - res) <= EPS * 10.) ? "Равны" : "Не равны") << endl << endl;;
    }

    return 0;
}

int main2() {
    setlocale(LC_ALL, "rus");

    double x0 = -0.1;
    double xn = 0.9;
    double dx = 0.2;

    const double EPS = 1e-6;

    for (double x = x0; x <= xn; x += dx) {
        double res = 0;

        double delta = 1;
        for (int i = 0; delta >= EPS; i++) {
            res += delta * (i % 2 ? -1 : 1);
            delta *= x * x;
        }

        cout << "f(" << x<< ") = " << res - 1 << endl;
        cout << "Check - " << (1. / (1. + x * x)) - 1 << endl;

        cout << "Сравнение: " << ( (abs((1. / (1. + x * x)) - res) <= EPS ) ? "Равны" : "Не равны") << endl << endl;;
    }

    return 0;
}