#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class MyString {
public:
    char* str;
    int length;
    MyString();
    MyString(char* val);
    MyString(const MyString& source);

    MyString& operator=(const MyString& rhs);
    friend bool operator==(const MyString& lhs, const MyString& rhs);
    friend ostream& operator<<(ostream& os, const MyString& obj);

    ~MyString();
};
