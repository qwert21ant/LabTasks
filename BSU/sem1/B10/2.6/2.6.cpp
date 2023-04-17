#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    double x0 = 1;
    double xm = 5;
    double dx = 0.5;

    int n;
    cout << "n = ";
    cin >> n;

    int cnt1s = 0, cnt1p = 0;
    int cnt2s = 0, cnt2p = 0;

    for (double x = x0; x <= xm; x += dx) {
        double res = 5;

        double st = x;
        double x2_1 = x * x;
        cnt1p++;
        for (int i = 1; i <= n; i++, st *= x2_1) {
            res += st * 2 * i;
            cnt1s++;
            cnt1p += 2;
        }

        cout << "f1(" << x << ") = " << res << endl;

        res = 0;
        
        double x2 = x * x;
        cnt2p++;
        for (int i = n; i > 0; i--) {
            res = res * x2 + 2 * i;
            cnt2s++;
            cnt2p += 2;
        }

        res = res * x + 5;
        cnt2p++;
        cnt2s++;

        cout << "f2(" << x << ") = " << res << endl;
        cout << endl;
    }

    cout << "Кол-во сложений/умножений: " << cnt1s << " / " << cnt1p << endl;
    cout << "Кол-во сложений/умножений (схема Горнера): " << cnt2s << " / " << cnt2p << endl;

    return 0;
}