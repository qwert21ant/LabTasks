#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int k;
    cout << "k = ";
    cin >> k;

    for (int i = 1; ; i++) {
        int t = i * i;
        int len = 1;
        while (t /= 10) len++;

        //cout << i << " - "  << i * i << " - " << len << ", k = " << k << endl;

        if (k > len) {
            k -= len;
            continue;
        }

        t = i * i;
        while (len != k) {
            t /= 10;
            len--;
        }

        cout << "Ответ: " << t % 10 << endl;
        break;
    }

    return 0;
}