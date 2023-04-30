#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"

MyString::MyString() : str{ nullptr } {
    str = new char[1];
    str[0] = '\0';
    this->length = 0;
}

MyString::MyString(char* chararray) {
    if (chararray == nullptr) {
        str = new char[1];
        str[0] = '\0';
        this->length = 0;
    }
    else {
        this-> length = strlen(chararray);
        str = new char[length + 1];
        strcpy(str, chararray);
    }
}

MyString::MyString(const MyString& string) {
    str = new char[string.length + 1];
    this->length = string.length;
    strcpy(str, string.str);
}

///construction
///
///
/// 
///operators

MyString& MyString::operator=(const MyString& rhs) {
    if (this == &rhs) {
        return *this;
    }
    delete[] str;
    str = new char[rhs.length + 1];
    strcpy(str, rhs.str);
    this->length = rhs.length;
    return *this;
}

ostream& operator<<(ostream& os, const MyString& string) {
    os << string.str;
    return os;
}

istream& operator>>(istream& istream, MyString& string) {
    char* buff = new char[1000];
    memset(&buff[0], 0, sizeof(buff));
    istream >> buff;
    string = MyString{ buff };
    delete[] buff;
    return istream;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
    if (lhs.length != rhs.length) {
        return false;
    }
    for (int i = 0; i < lhs.length; i++) {
        if (lhs.str[i] != rhs.str[i]) {
            return false;
        }
    }
    return true;
}



MyString::~MyString() {
    delete[] str;
}