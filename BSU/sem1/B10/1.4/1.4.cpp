// 1.4. ЛОГИЧЕСКОЕ ВЫРАЖЕНИЕ В УСЛОВНОМ ОПЕРАТОРЕ

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int sx, sy, kx, ky;
    
    cout << "Координаты слона: ";
    cin >> sx >> sy;

    cout << "Координаты коня: ";
    cin >> kx >> ky;

    if (sx < 1 || sx > 8 || sy < 1 || sy > 8 || kx < 1 || kx > 8 || ky < 1 || ky > 8) {
        cout << "Неверные значения" << endl;
        return 0;
    }

    int dx = abs(sx - kx);
    int dy = abs(sy - ky);

    if (dx == dy)
        cout << "Слон бьёт коня" << endl;

    if (dx * dy == 2)
        cout << "Конь бьёт слона" << endl;

    if ((dx + dy) % 2 == 0)
        cout << "После одного хода слона он будет бить коня" << endl;        

    if (
         (
           (kx - 1) % 7 == 0 && (ky - 1) % 7 == 0 || // конь в углу или 
           (sx - 1) % 7 == 0 && (sy - 1) % 7 == 0    // слон в углу
         ) && dx == 1 && dy == 1                     // другая фигура рядом с первой по диагонали
       ) {
        // в таком случае конь не сможет побить слона после 1го хода
    } else if (dx <= 4 && dy <= 4 && (dx + dy) % 2 == 0 && (dx != dy || (dx % 2 == 1)))
        cout << "После одного хода коня он будет бить слона" << endl;

    /*auto f1 = [=](int x, int y) {
        return abs(x - 4) == 2 || abs(x - 4) == 3;
    };

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++)
            cout << (f1(i, j) ? '#' : '.');
        cout << endl;
    }
    cout << endl;*/

    system("pause");
    return 0;
}