#include <iostream>
#include <iomanip>

#include "funcs.h"

using namespace std;

double func(double x, double s, double t) {
    return t * (1 + s * x * s * x) / (1 + x * x * x);
}

int main() {
    setlocale(LC_ALL, "rus");

    /* constants */
    const double s1 = 1, s2 = 5;
    const double t1 = 0.5, t2 = 2.5;
    const double ds = 1, dt = 0.5;
    const double a = 3, b = 4.254;
    const double eps = 1e-6;

    cout << "| s      | t      | Int    | kIter  |" << endl;
    cout << "+--------+--------+--------+--------+" << endl;
    for (double s = s1; s <= s2; s += ds) {
        for (double t = t1; t <= t2; t += dt) {
            int kIter;
            double res = integral_eps(func, s, t, a, b, eps, kIter);

            cout << "|" << setw(8) << s << "|";
            cout << setw(8) << t << "|";
            cout << setw(8) << res << "|";
            cout << setw(8) << kIter << "|" << endl;
        }
    }

    return 0;
}