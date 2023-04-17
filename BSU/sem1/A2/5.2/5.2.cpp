#include <iostream>

using namespace std;

int func1(int num) {
    int s = num % 10 + (num / 10) % 10 + (num / 100) % 10 + (num / 1000) % 10;
    return s;
}

void func2(int num, int& res) {
    int s = num % 10 + (num / 10) % 10 + (num / 100) % 10 + (num / 1000) % 10;
    res = s;
}

void func3(int num, int* res) {
    int s = num % 10 + (num / 10) % 10 + (num / 100) % 10 + (num / 1000) % 10;
    *res = s;
}

int main() {
    setlocale(LC_ALL, "rus");

    int num;
    cout << "Введите число: ";
    cin >> num;

    cout << "Результат:" << endl;
    
    int res;
    res = func1(num);
    cout << "  Способ 1: " << res << endl;

    func2(num, res);
    cout << "  Способ 2: " << res << endl;

    func3(num, &res);
    cout << "  Способ 3: " << res << endl;

    return 0;
}