// 1.2. ОБЛАСТЬ НА ПЛОСКОСТИ

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    double x, y;

    cout << "x = ";
    cin >> x;

    cout << "y = ";
    cin >> y;

    if ((y >= (x - 2) * (x - 2) - 3) && x >= 0 && ((y >= 0 && y <= x) || (y < 0 && -y >= x)))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    system("pause");
    return 0;
}