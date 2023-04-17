#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int BASE = 1e5;
const int DIG = 5;

void printNum(int* num, int len) {
    if (len) cout << num[len - 1];
    for (int i = len - 2; i >= 0; i--) {
        cout << setfill('0') << setw(DIG) << num[i];
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int n;
    cout << "Введите число: ";
    cin >> n;

    int num[100000];
    
    num[0] = n;
    int len = 1;

    while(--n != 1) {
        int carry = 0;
        for (int i = 0; i < len; i++) {
            num[i] = num[i] * n + carry;
            carry = num[i] / BASE;
            num[i] %= BASE;
        }
        if (carry)
            num[len++] = carry;
    }

    printNum(num, len);

    int res = 0;
    for (int i = 0; i < len; i++) {
        do {
            res += num[i] % 10 == 3;
        } while (num[i] /= 10);
    }

    cout << "Количество 3: " << res << endl;

    return 0;
}