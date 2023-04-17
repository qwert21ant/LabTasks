#include <iostream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    char delim[] = " .,:;!?-()";

    char str[100000];
    cout << "Введите строку: ";
    cin.getline(str, 100000, '\n');

    char sl[100][1000];

    /*for (int i = 0; i < strlen(str); i++) {
        if (strchr(delim, str[i])) {
            sl[n][k] = 0;
            k = 0;
            n++;
        } else {
            sl[n][k] = str[i];
            k++;
        }
    }*/

    int chars[256];
    int flg = 0;

    char* tmp = strtok_s(str, delim, (char**) sl);
    while (tmp != nullptr) {
        flg = 0;

        if (strstr(delim, tmp) != nullptr)
            continue;

        //for (int j = 0; j < 256; j++) chars[j] = 0;
        //for (int j = 0; j < strlen(tmp); j++) chars[tmp[j]]++;
        //for (int j = 0; j < 256; j++)
        //    if (chars[j] >= 2) {
        //        flg = 1;
        //        break;
        //    }
        for (int j = 0; j < strlen(tmp); j++)
            if (isdigit(tmp[j])) {
                flg = 1;
                break;
            }

        if (!flg) cout << tmp << " ";


        tmp = strtok_s(nullptr, delim, (char**)sl);
    }

    return 0;
}