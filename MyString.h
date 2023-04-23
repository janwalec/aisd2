#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class MyString {
    char* str;
public:
    MyString();
    MyString(char* val);
    MyString(const MyString& source);

    MyString& operator=(const MyString& rhs);
    friend bool operator==(const MyString& lhs, const MyString& rhs);
    friend ostream& operator<<(ostream& os, const MyString& obj);
    friend istream& operator>>(istream& is, MyString& obj);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    ~MyString();
};
