/// <inspiration>
/// https://www.geeksforgeeks.org/
/// </inspiration>
#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class MyString {
public:
    char* str;
    int length;
    MyString();
    MyString(char* chararray);
    MyString(const MyString& string);
    MyString& operator=(const MyString& rhs);
    friend bool operator==(const MyString& lhs, const MyString& rhs);
    friend ostream& operator<<(ostream& os, const MyString& string);
    friend istream& operator>>(istream& istream, MyString& string);

    ~MyString();
};
