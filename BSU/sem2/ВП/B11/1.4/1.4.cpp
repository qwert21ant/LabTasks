#include <iostream>
#include <iomanip>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

double f1(double x, double s) {
    return (x + 1) * (x + 1) - 4;
}

double f2(double x, double s) {
    double c = cos(M_PI * x);
    return c * c - pow(M_E, pow(x, s)) + 1;
}

using func = decltype(f1)*;

/*double M1(func f, double a, double b, double s, double eps, double& val, int& kIter) {
    kIter = 0;
    double c = 0.;
    
    for (; b - a > eps; kIter++) {
        c = (a + b) / 2.;
        if (f(a, s) * f(c, s) < 0)
            b = c;
        else
            a = c;
    }

    c = (a + b) / 2.;
    val = f(c, s);
    return c;
}*/

double M3(func f, double a, double b, double s, double eps, int& kIter) {
    kIter = 0;
    double x = 0.;

    while (true) {
        double fa = f(a, s);
        double fb = f(b, s);
        x = a - fa / (fb - fa) * (b - a);

        if (fa * f(x, s) < 0)
            b = x;
        else
            a = x;

        kIter++;
        if (abs(f(x, s)) < eps) break;
    }

    return x;
}

int main() {
    setlocale(LC_ALL, "rus");

    /* constants */
    const double a[] = { 0, 0 };
    const double b[] = { 3, 2 };
    const double s1 = 0.9, s2 = 1.2;
    const double ds = 0.02;
    const double eps = 1e-6;

    cout << fixed << setprecision(3);

    cout << "           Func 1" << endl;
    cout << "| x      | F(x)   | kIter  |" << endl;
    cout << "+--------+--------+--------+" << endl;
    int kIter;
    double x = M3(f1, a[0], b[0], 0, eps, kIter);

    cout << "|" << setw(8) << x << "|";
    cout << setw(8) << f1(x, 0) << "|";
    cout << setw(8) << kIter << "|" << endl;
    cout << endl;


    cout << "                Func 2" << endl;
    cout << "| s      | x      | F(x)   | kIter  |" << endl;
    cout << "+--------+--------+--------+--------+" << endl;
    for (double s = s1; s <= s2; s += ds) {
        int kIter;
        double x = M3(f2, a[1], b[1], s, eps, kIter);

        cout << "|" << setw(8) << s << "|";
        cout << setw(8) << x << "|";
        cout << setw(8) << f2(x, s) << "|";
        cout << setw(8) << kIter << "|" << endl;
    }

    return 0;
}