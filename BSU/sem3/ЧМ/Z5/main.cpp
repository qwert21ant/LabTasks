#include <iostream>
#include <iomanip>

#include "Integration.hpp"

using namespace std;

double f1(double x) {
  return 0.1 * x * x / log10(x);
}

double f2(double x, double y) {
  return 4 - x * x - y * y;
}

int main() {
  {
    double a = 2.0;
    double b = 3.104;

    cout << setprecision(10);

    double res = Integration::integrateXTrapezoid(f1, a, b);
    cout << "Result (trapezoid method): " << res << endl;

    res = Integration::integrateXSimpson(f1, a, b);
    cout << "Result (Simpson method): " << res << endl;

    cout << endl;
  }

  {
    double a = -1.0;
    double b = 1.0;
    double c = -1.0;
    double d = 1.0;

    cout << setprecision(10);

    double res = Integration::integrateXYSimpson(f2, a, b, c, d);
    cout << "Result XY (Simpson method): " << res << endl;
  }

  return 0;
}