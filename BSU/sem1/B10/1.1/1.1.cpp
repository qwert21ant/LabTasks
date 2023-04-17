// 1.1. ВЫЧИСЛЕНИЯ ПО ФОРМУЛАМ. СТАНДАРТНЫЕ МАТЕМАТИЧЕСКИЕ ФУНКЦИИ

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int s, t;
    double x;

    cout << "s = ";
    cin >> s;

    cout << "t = ";
    cin >> t;

    cout << "x = ";
    cin >> x;
   
    double y = sqrt((double) t) * (3. * pow(x, (double) t)) / sqrt(1. + pow(x, (double) s));

    cout << "y = " << y << endl;

    system("pause");
    return 0;
}