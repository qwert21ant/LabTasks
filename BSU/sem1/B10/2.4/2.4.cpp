#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const double EPS = 1e-6;

    cout << "Последовательность: ";

    int max_res = 0;
    int cur_res = 0;

    int d;
    while (cin>>d, d) {
        bool st = 0;

        for (int v = 1; v <= d; v *= 3) {
            if (d == v) {
                st = 1;
                break;
            }
        }

        if (st) {
            cur_res++;
            max_res = cur_res > max_res ? cur_res : max_res;
        } else {
            cur_res = 0;
        }
    }

    cout << "Ответ: " << max_res << endl;

    return 0;
}