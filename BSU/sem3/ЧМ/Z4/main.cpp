#include <iostream>

#include "LSApprox.hpp"

using namespace std;

int main() {
  vector<double> x = { 2.4, 3.5, 5.0, 6.89, 10.0 };
  vector<double> y = { 0.0141, 0.0281, 0.0562, 0.1125, 0.225 };

  try {
    vector<double> coefs = LSApprox::findCoef(x, y, 2);
    cout << "All coefficients: " << coefs[0] << ", " << coefs[1] << ", " << coefs[2] << endl;
    cout << "Solution: P = " << coefs[0] << " + " << coefs[2] << " * v^2" << endl;

    double dev = LSApprox::countDeviation(x, y, coefs);
    cout << "Deviation: " << dev << endl;
  } catch (exception e) {
    cout << e.what() << endl;
  }

  return 9;
}