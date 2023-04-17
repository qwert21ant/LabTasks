#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
        
    char str[1000];
    cout << "Введите строку: ";
    cin >> str;

    bool isnum = true;
    for (int i = 0; isnum && i < strlen(str); i++)
        if (!isdigit(str[i]))
            isnum = false;
    
    bool isid = true;
    if (isdigit(str[0])) isid = false;
    for (int i = 0; isid && i < strlen(str); i++)
        if (!isalnum(str[i]) && strchr("_", str[i]) == nullptr)
            isid = false;
    
    if (isid) cout << "Строка является идентификатором" << endl;
    if (isnum) cout << "Строка является целым числом" << endl;
    return 0;
}