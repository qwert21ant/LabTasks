#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

template <typename T>
void merge_sort(T* data, int n) {
    if (n == 1)
        return;

    int b1 = n / 2, b2 = (n + 1) / 2;

    merge_sort(data, b1);
    merge_sort(data + b1, b2);

    T* tmp = new T[n];

    for (int i = 0, i1 = 0, i2 = 0; i < n; i++) {
        if (i1 < b1 && i2 < b2) {
            if (data[i1] < data[b1 + i2])
                tmp[i] = data[i1++];
            else
                tmp[i] = data[b1 + i2++];
        }
        else if (i1 < b1) {
            tmp[i] = data[i1++];
        }
        else {
            tmp[i] = data[b1 + i2++];
        }
    }

    memcpy(data, tmp, sizeof(T) * n);

    delete[] tmp;
}

char* strx(const char* s) {
    char* res = new char[strlen(s) + 1];
    strcpy(res, s);
    return res;
}

void merge_sort(char** data, int n) {
    if (n == 1)
        return;

    int b1 = n / 2, b2 = (n + 1) / 2;

    merge_sort(data, b1);
    merge_sort(data + b1, b2);

    char** tmp = new char* [n];

    for (int i = 0, i1 = 0, i2 = 0; i < n; i++) {
        if (i1 < b1 && i2 < b2) {
            if (strcmp(data[i1], data[b1 + i2]) < 0)
                tmp[i] = strx(data[i1++]);
            else
                tmp[i] = strx(data[b1 + i2++]);
        }
        else if (i1 < b1) {
            tmp[i] = strx(data[i1++]);
        }
        else {
            tmp[i] = strx(data[b1 + i2++]);
        }
    }

    for (int i = 0; i < n; i++)
        delete[] data[i];
    memcpy(data, tmp, sizeof(char*) * n);

    delete[] tmp;
}

template <typename T>
void output(T* data, int len) {
    for (int i = 0; i < len; i++)
        cout << data[i] << " ";
    cout << endl;
}

void gen_rand(int* data, int len) {
    for (int i = 0; i < len; i++)
        data[i] = rand() % 100;
}

void gen_rand(double* data, int len) {
    for (int i = 0; i < len; i++)
        data[i] = (rand() % 10000) / 100.;
}

void gen_rand(char** data, int len) {
    for (int i = 0; i < len; i++) {
        int x = rand() % 10 + 5;
        data[i] = new char[x + 1];
        for (int j = 0; j < x; j++)
            data[i][j] = 'a' + rand() % 26;
        data[i][x] = 0;
    }
}