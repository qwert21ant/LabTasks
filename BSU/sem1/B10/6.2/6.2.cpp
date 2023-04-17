#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>

#include <bitset>

using namespace std;

union Struct {
    unsigned short val;
    struct {
        unsigned short let : 3;
        unsigned short form : 4;
        unsigned short num : 9;
    };
};

bool comp(Struct& a, Struct& b) {
    return a.val > b.val;
}

bool comp2(Struct& a, Struct& b) {
    if (a.num != b.num)
        return a.num > b.num;

    if (a.form != b.form)
        return a.form > b.form;

    return a.let > b.let;
}

void generate(Struct data[100], int n) {
    for (int i = 0; i < n; i++) {
        data[i].val = 0;
        data[i].num = rand() % 277 + 1;
        data[i].form = rand() % 11 + 1;
        data[i].let = rand() % 9;
    }
}

void output(Struct data[100], int n) {
    cout << "| " << setw(5) << "Номер" << " | " << setw(5) << "Класс";
    cout << " | " << setw(5) << "Буква" << " |" << endl;

    cout << setfill('-');
    cout << "+" << setw(8) << "+" << setw(8) << "+" << setw(8) << "+" << endl;

    cout << setfill(' ');

    for (int i = 0; i < n; i++) {
        cout << "| " << setw(5) << data[i].num << " | " << setw(5) << (unsigned int)data[i].form;
        cout << " | " << setw(5) << char('А' + data[i].let) << " |";
        cout << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    srand(time(0));

    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    Struct data[1000];
    Struct data2[1000];

    int n;
    cout << "Введите количество записей (до 1000): ";
    cin >> n;

    generate(data, n);

    cout << "Сгенерированные записи: " << endl;
    output(data, n);

    for (int i = 0; i < n; i++)
        data2[i] = data[i];

    sort(data, data + n, comp);

    cout << "Отсортированные записи (через val): " << endl;
    output(data, n);

    sort(data2, data2 + n, comp2);

    cout << "Отсортированные записи: " << endl;
    output(data2, n);

    bool flg = true;
    for(int i = 0; i < n; i++)
        if (data[i].val != data2[i].val) {
            flg = false;
            break;
        }

    cout << "Сравнение: " << (flg ? "равны" : "не равны") << endl;

    const int max_sz = 65536;
    unsigned short mas[max_sz];
    for (int i = 0; i < max_sz; i++)
        mas[i] = 0;

    for (int i = 0; i < n; i++)
        mas[data[i].val]++;

    Struct res[100];
    int res_sz = 0;
    for (int i = 0; i < max_sz; i++) {
        if (mas[i] >= 2) {
            res[res_sz++].val = i;
        }
    }

    if (!res_sz)
        cout << "Нет повторяющихся записей" << endl;
    else {
        cout << "Повторяющиеся записи: " << endl;
        output(res, res_sz);
    }
    
    return 0;
}