#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"


MyString& MyString::operator=(const MyString& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] str;
    str = new char[strlen(rhs.str) + 1];
    strcpy(str, rhs.str);
    return *this;
}


MyString operator+(const MyString& lhs, const MyString& rhs) {
    int length = strlen(lhs.str) + strlen(rhs.str);
    char* buff = new char[length + 1];
    strcpy(buff, lhs.str);
    strcat(buff, rhs.str);
    MyString temp{ buff };
    delete[] buff;
    return temp;
}

istream& operator>>(istream& is, MyString& obj) {
    char* buff = new char[1000];
    memset(&buff[0], 0, sizeof(buff));
    is >> buff;
    obj = MyString{ buff };
    delete[] buff;
    return is;
}

ostream& operator<<(ostream& os, const MyString& obj) {
    os << obj.str;
    return os;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    if (strlen(lhs.str) != strlen(rhs.str)) {
        return false;
    }

    for (int i = 0; i < strlen(lhs.str); i++) {
        if (lhs.str[i] != rhs.str[i]) {
            return false;
        }
    }
        
    return true;
}

MyString::MyString() : str{ nullptr } {
    str = new char[1];
    str[0] = '\0';
}

MyString::MyString(char* val) {
    if (val == nullptr) {
        str = new char[1];
        str[0] = '\0';
    } else {
        str = new char[strlen(val) + 1];
        strcpy(str, val);
    }
}

MyString::MyString(const MyString& source) {
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
}


MyString::~MyString() {
    delete[] str;
}