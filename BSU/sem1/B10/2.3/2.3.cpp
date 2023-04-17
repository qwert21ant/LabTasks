#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int cnt = 0;
    for (int n = 1000; n < 10000; n++) {

        bool prost = 1;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                prost = 0;
                break;
            }
        }

        if (!prost)
            continue;

        int t = n;
        int m = 0;
        do {
            int d = t % 10;
            m *= 10;
            m += d;
        } while (t /= 10);

        prost = 1;
        for (int i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                prost = 0;
                break;
            }
        }

        if (prost) {
            //cout << n << " ";
            cnt++;
        }
    }

    cout << "Ответ: " << cnt << endl;

    return 0;
}