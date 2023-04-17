#include <iostream>
#include <string.h>
#include <limits>

using namespace std;
/*
char toChar(unsigned int n) {
    if (n < 10) return '0' + n;
    return 'a' + n - 10;
    //(n < 10) ? ('0' + n) : ('a' + n - 10)
}

int toInt(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    return ch - 'a' + 10;
    //('0' <= ch && ch <= '9') ? (ch - '0') : (ch - 'a' + 10)
}

class Number {
private:
    int data[10000];
    int len;
    int base;

public:
    Number() : len(1), base(10) {
        data[0] = 0;
    };
    ~Number() = default;

    Number(char* str, int base) : base(base) {
        _strrev(str);  

        len = strlen(str);
        for (int i = 0; i < len; i++)
            data[i] = toInt(str[i]);
    }

    void rebase(int newbase) {
        int newdata[10000];
        int newlen = 0;

        while (!!*this)
            newdata[newlen++] = div(newbase);

        len = newlen;
        for (int i = 0; i < newlen; i++) {
            data[i] = newdata[i];
        }
    }

    int div(int val) {
        int carry = 0;
        for (int i = len - 1; i >= 0; i--) {
            int cur = data[i] + carry * base;
            data[i] = cur / val;
            carry = cur % val;
        }
        while (data[len - 1] == 0 && len > 1) {
            len--;
        }
        return carry;
    }

    bool operator !() {
        return len == 1 && data[0] == 0;
    }

    friend ostream& operator <<(ostream&, Number&);
};

ostream& operator <<(ostream& out, Number& num) {
    for (int i = num.len - 1; i >= 0; i--)
        out << toChar(num.data[i]);

    return out;
}
*/

int main(){
    setlocale(LC_ALL, "rus");

    cout << "Число: ";
    char s[1000];
    cin >> s;

    cout << "p = ";
    int p;
    cin >> p;

    cout << "q = ";
    int q;
    cin >> q;

    int data[10000];
    int len = strlen(s);
    int base = p;

    _strrev(s);

    len = strlen(s);
    for (int i = 0; i < len; i++)
        data[i] = ('0' <= s[i] && s[i] <= '9') ? (s[i] - '0') : (s[i] - 'a' + 10);


    int newdata[10000];
    int newlen = 0;

    while (!(len == 1 && data[0] == 0)) {
        int carry = 0;
        for (int i = len - 1; i >= 0; i--) {
            int cur = data[i] + carry * base;
            data[i] = cur / q;
            carry = cur % q;
        }
        while (data[len - 1] == 0 && len > 1) {
            len--;
        }
        newdata[newlen++] = carry;
    }

    for (int i = newlen - 1; i >= 0; i--)
        cout << char((newdata[i] < 10) ? ('0' + newdata[i]) : ('a' + newdata[i] - 10));
        //cout << toChar(newdata[i]);

    /*Number num(s, p);
    num.rebase(q);

    cout << num << endl;*/
    return 0;
}