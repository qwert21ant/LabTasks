#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int MIN = 1000;

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    bool a[MIN * 10];
    for (int i = 0; i < MIN * 10; i++)
        a[i] = 0;

    a[1] = 1;
    for (int i = 2; i * i < MIN * 10; i++) {
        if (a[i]) continue;
        for (int j = i * i; j < MIN * 10; j += i)
            a[j] = 1;
    }

    int cnt = 0;
    for (int n = MIN; n < MIN * 10; n++) {
        if (a[n])
            continue;

        int t = n;
        int m = 0;
        do {
            int d = t % 10;
            m *= 10;
            m += d;
        } while (t /= 10);

        if (!a[m])
            cnt++;
    }

    cout << "Ответ: " << cnt << endl;

    return 0;
}