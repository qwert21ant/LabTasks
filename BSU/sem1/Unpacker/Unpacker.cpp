﻿#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

const int sz = 244;
const BYTE arr[] = { 0xd4, 0x3e, 0x85, 0x60, 0x25, 0xb0, 0xd5, 0xf0, 0x26, 0xc6, 0x76, 0x63,
                            0xee, 0xad, 0x06, 0x3f, 0xb1, 0xb1, 0x10, 0xff, 0x91, 0xb1, 0x10, 0x7f,
                            0x77, 0x01, 0x12, 0xb0, 0x0e, 0x35, 0xc6, 0x27, 0xd5, 0xe7, 0xea, 0xb5,
                            0xa9, 0xe9, 0x55, 0x63, 0x2e, 0xbe, 0xb2, 0x6d, 0x66, 0xbb, 0x11, 0x7b,
                            0x62, 0xda, 0xbb, 0x20, 0x63, 0x18, 0x9b, 0xfc, 0xcc, 0xa3, 0x15, 0x29,
                            0xb3, 0x8d, 0x2f, 0x0e, 0xf8, 0xb6, 0xed, 0x16, 0x5f, 0xe7, 0xe3, 0xcd,
                            0x93, 0xba, 0xc5, 0x86, 0x65, 0x5a, 0xe8, 0x40, 0x1f, 0xe0, 0x01, 0x61,
                            0xb0, 0xcb, 0xd4, 0xdc, 0x96, 0x4d, 0x2d, 0x19, 0x7d, 0x72, 0x90, 0xdf,
                            0xbc, 0x2b, 0x03, 0x7c, 0xf2, 0x33, 0x21, 0xbb, 0xd8, 0xbc, 0x05, 0x43,
                            0x2d, 0x31, 0xfc, 0x59, 0x17, 0xef, 0x95, 0x91, 0x6f, 0x9f, 0xb0, 0x05,
                            0x81, 0x82, 0x0b, 0xd3, 0x46, 0x5a, 0x9a, 0x51, 0x46, 0x03, 0x0c, 0x29,
                            0x93, 0xf3, 0x5c, 0xc7, 0xb8, 0x76, 0xcb, 0xfc, 0x58, 0x8c, 0xcd, 0xd1,
                            0x9e, 0xf0, 0x0a, 0x55, 0xcb, 0x9a, 0x3b, 0x31, 0xa5, 0xe2, 0xa3, 0x07,
                            0x5c, 0x39, 0xc8, 0x49, 0x58, 0x86, 0x5f, 0xb2, 0x62, 0xf0, 0xd5, 0x46,
                            0x83, 0xb8, 0x12, 0xa4, 0x2b, 0x14, 0x26, 0xd7, 0x43, 0xe4, 0xb9, 0x3e,
                            0x65, 0x35, 0x72, 0x3a, 0x6f, 0x2d, 0x19, 0xac, 0xee, 0x4c, 0xa7, 0x6e,
                            0xeb, 0xe0, 0xb3, 0x72, 0xd6, 0x5e, 0x97, 0x4f, 0x98, 0x10, 0x7f, 0x01,
                            0xb8, 0x26, 0xbd, 0x13, 0xf4, 0x4d, 0x9f, 0x1d, 0xac, 0x8a, 0x41, 0x4b,
                            0xda, 0xdd, 0x4f, 0x7f, 0x55, 0x24, 0x14, 0xe8, 0x97, 0x03, 0x40, 0xb9,
                            0x87, 0xed, 0xde, 0x30, 0xed, 0x67, 0xe0, 0xb2, 0x1d, 0x50, 0xc2, 0x73,
                            0x5c, 0xd0, 0xc7, 0xbf };


class Message {
public:
    Message(const BYTE* data, int size) : _size(size), _pwd(0) {
        _data = new BYTE[_size];
        memcpy(_data, data, _size);
    }

    Message(const Message& msg) : _size(msg._size), _pwd(msg._pwd) {
        _data = new BYTE[_size];
        memcpy(_data, msg._data, _size);
    }

    Message& Swap(Message& msg) {
        swap(_size, msg._size);
        swap(_data, msg._data);
        swap(_pwd, msg._pwd);
        return *this;
    }

    Message& operator=(Message msg) {
        return Swap(msg);
    }

    ~Message() {
        delete[] _data;
    }


    void SetPassword(DWORD pwd) {
        _pwd = pwd;
    }

    DWORD GetPassword() const {
        return _pwd;
    }

    bool CheckData() const {
        for (int i = 0; i < _size; i++)
            if (!CheckValue(_data[i]))
                return false;

        return true;
    }

    void Encode() {
        srand(_pwd);
        for (int i = 0; i < _size; i++)
            _data[i] ^= rand();
    }

    bool TryDecode() {
        BYTE tmp;

        for (DWORD pwd = 0; pwd < ULONG_MAX; pwd++) {
            srand(pwd);

            int i = 0;
            for (; i < _size; i++) {
                tmp = _data[i] ^ rand();
                if (!CheckValue(tmp))
                    break;
            }

            if (i == _size) {
                _pwd = pwd;
                Encode();
                return true;
            }
        }

        return false;
    }


    bool operator==(const Message& msg) const {
        if (_size != msg._size)
            return false;

        return memcmp(_data, msg._data, _size) == 0;
    }

    friend ostream& operator<<(ostream&, const Message&);

private:
    BYTE* _data;
    int _size;

    DWORD _pwd;

    bool CheckValue(BYTE ch) const {
        if (ch >= 'a' && ch <= 'z')
            return true;

        if (ch >= 'A' && ch <= 'Z')
            return true;

        if (ch == ' ' || ch == ',' || ch == '.')
            return true;

        return false;
    }
};

ostream& operator<<(ostream& out, const Message& msg) {
    if (!msg.CheckData())
        out << "-- Bad data --";
    else {
        for (int i = 0; i < msg._size; i++)
            out << char(msg._data[i]);
    }

    return out;
}

int main() {
    setlocale(LC_ALL, "rus");

    Message msg(arr, sz);

    msg.SetPassword(0);

    bool res = msg.TryDecode();

    cout << "TryDecode: " << (res ? "success" : "failed") << endl;
    if (res) {
        cout << "Password: " << msg.GetPassword() << endl;
        cout << "Data: " << msg << endl;
    }

    return 0;
}