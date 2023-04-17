// 1.3. УСЛОВНЫЙ ОПЕРАТОР

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    double x1, x2, x3, x4;

    cout << "x1 x2 x3 x4: ";
    cin >> x1 >> x2 >> x3 >> x4;

/*    double mx = x1;
    if (x2 > mx) mx = x2;
    if (x3 > mx) mx = x3;
    if (x4 > mx) mx = x4;

    double mn = x1;
    if (x2 < mn) mn = x2;
    if (x3 < mn) mn = x3;
    if (x4 < mn) mn = x4;

    double sr1;
    if (x1 > mn && x1 < mx)
        sr1 = x1;
    else if (x2 > mn && x2 < mx)
        sr1 = x2;
    else if (x3 > mn && x3 < mx)
        sr1 = x3;
    else
        sr1 = x4;

    double sr2 = x1 + x2 + x3 + x4 - sr1 - mn - mx;*/

    double a, b;
    double y1, y2, y3, y4;
    a = x1 > x2 ? x1 : x2;
    b = x3 > x4 ? x3 : x4;

    if (a > b) {
        y1 = x1 + x2 - a;
        y2 = a;
        y3 = b;
        y4 = x3 + x4 - b;
    } else {
        y1 = x3 + x4 - b;
        y2 = b;
        y3 = a;
        y4 = x1 + x2 - a;
    }

    cout << y1 << " " << y2 << " " << y3 << " " << y4 << endl;

    system("pause");
    return 0;
}