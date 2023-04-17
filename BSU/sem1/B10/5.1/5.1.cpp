#include <iostream>

using namespace std;

const double EPS = 10e-6;

double fact(int x) {
    if (x == 0) return 1;
    return x * fact(x - 1);
}

double func(double x, int* cnt) {
    double res = 0;
    double num = 1;

    double a = 1; // (-1)^k
    double b = x * x; // x^(k+2)
    //double c = 2; // (K+2)!

    int k = 1;

    do {
        a *= -1;
        b *= x;
        //c *= k + 2;

        num = a * b / fact(k + 2) / (k + 1);

        res += num;
        k++;
    } while (num >= EPS || num <= -EPS);

    *cnt = k-1;
    return res;
}

void func(double x, double& res, int& cnt) {
    res = 0;
    double num = 1;

    double a = 1; // (-1)^k
    double b = x * x; // x^(k+2)
    //double c = 2; // (K+2)!

    int k = 1;

    do {
        a *= -1;
        b *= x;
        //c *= k + 2;

        num = a * b / fact(k + 2) / (k + 1);

        res += num;
        k++;
    } while (num >= EPS || num <= -EPS);

    cnt = k - 1;
}

int main(){
    double x;
    cout << "x = ";
    cin >> x;

    {
        cout << "1:" << endl;

        int cnt;
        cout << "answer: " << func(x, &cnt) << endl;
        cout << "count: " << cnt << endl << endl;
    }

    {
        cout << "2:" << endl;

        double ans;
        int cnt;
        func(x, ans, cnt);
        cout << "answer: " << ans << endl;
        cout << "count: " << cnt << endl;
    }

    return 0;
}