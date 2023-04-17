#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

using f_type = double (*)(double, double, double);

double integral(f_type f, double s, double t, double a, double b, int n) {
    const double h = (b - a) / n;
    double s1 = 0, s2 = 0;

    for (int i = 1; i < n; i += 2) {
        s1 += f(a + i * h, s, t);
        s2 += f(a + (i + 1) * h, s, t);
    }

    return h / 3 * (f(a, s, t) + 4 * s1 + 2 * s2);
}

double integral_eps(f_type f, double s, double t, double a, double b, double eps, int& kIter) {
    kIter = 0;
    int n = 2;

    double int1;
    double int2 = integral(f, s, t, a, b, n);
    do {
        int1 = int2;
        n *= 2;

        int2 = integral(f, s, t, a, b, n);
        kIter++;
    } while (abs(int1 - int2) > eps);

    return int2;
}