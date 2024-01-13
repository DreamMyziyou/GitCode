//
// Created by WeslyChen on 2024/1/12.
//

#include "String.h"

using namespace std;

String& String::operator=(char c)
{
    mImpl = c;
    return *this;
}

String& String::operator=(const char* c)
{
    mImpl = c;
    return *this;
}

String& String::operator+=(char c)
{
    mImpl += c;
    return *this;
}

String& String::operator+=(const char* c)
{
    mImpl += c;
    return *this;
}

String& String::operator+=(const String& str)
{
    mImpl += str.mImpl;
    return *this;
}