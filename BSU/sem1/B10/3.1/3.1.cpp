#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum MODE {
    STATIC = 1,
    RANDOM = 2,
    INPUT = 3
};

int main(){
    setlocale(LC_ALL, "rus");
    srand(time(0));

    int n;
    cout << "Введите размер масиива (не больше 10000): ";
    cin >> n;

    int a[10000];

    int mode;
    cout << "Выберите способ инициализации значений: встроенные значения(1), рандом(2), ввод(3): ";
    cin >> mode;

    if (mode == STATIC) {
        int values[] = {1, 2, 3, 4, 3, 2};
        cout << "Массив: ";
        for (int i = 0; i < n; i++) {
            a[i] = values[i % 6];
            cout << a[i] << " ";
        }
        cout << endl;
    } else if (mode == MODE::RANDOM) {
        int d;
        cout << "Введите верхнюю границу значений: ";
        cin >> d;

        cout << "Сгенерированный массив: ";
        for (int i = 0; i < n; i++) {
            a[i] = rand() % d;
            cout << a[i] << " ";
        }
        cout << endl;
    } else if (mode == MODE::INPUT) {
        cout << "Введите значения через пробел: ";

        for (int i = 0; i < n; i++)
            cin >> a[i];
    } else {
        cout << "Неверный ввод" << endl;
        return 0;
    }

    int mul = 1, mdl = 1;
    int ul = 1, dl = 1;
    for (int i = 1; i < n; i++) {
        if (a[i - 1] < a[i]) {
            ul++;
            mdl = mdl > dl ? mdl : dl;
            dl = 1;
        } else if (a[i - 1] > a[i]) {
            dl++;
            mul = mul > ul ? mul : ul;
            ul = 1;
        } else {
            ul++;
            dl++;
        }
    }

    mdl = mdl > dl ? mdl : dl;
    mul = mul > ul ? mul : ul;

    cout << "Ответ: " << (mul > mdl ? mul : mdl) << endl;

    return 0;
}