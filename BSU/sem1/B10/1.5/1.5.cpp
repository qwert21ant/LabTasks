// 1.5. ВЕТВЛЕНИЯ

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    double x1, x2, x3, x4;
    double y1, y2, y3, y4;

    cout << "x1 y1: ";
    cin >> x1 >> y1;

    cout << "x2 y2: ";
    cin >> x2 >> y2;

    cout << "x3 y3: ";
    cin >> x3 >> y3;

    cout << "x4 y4: ";
    cin >> x4 >> y4;

    double t;
    t = x1 > x2 ? x1 : x2;
    x1 = x1 + x2 - t;
    x2 = t;

    t = y1 > y2 ? y1 : y2;
    y1 = y1 + y2 - t;
    y2 = t;

    t = x3 > x4 ? x3 : x4;
    x3 = x3 + x4 - t;
    x4 = t;

    t = y3 > y4 ? y3 : y4;
    y3 = y3 + y4 - t;
    y4 = t;

    cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    cout << x3 << " " << y3 << " " << x4 << " " << y4 << endl;

    if (x3 <= x1 && x2 <= x4 && y3 <= y1 && y2 <= y4 ||
        x1 <= x3 && x4 <= x2 && y1 <= y3 && y4 <= y2)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    system("pause");
    return 0;
}