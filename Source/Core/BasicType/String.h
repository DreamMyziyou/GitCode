//
// Created by WeslyChen on 2024/1/12.
//

#ifndef WORKENGINE_STRING_H
#define WORKENGINE_STRING_H

#include <string>

#include "BasicType.h"

class String final
{
public:
    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator==(const String& lhs, const char* rhs);
    friend bool operator==(const char* lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const char* rhs);
    friend bool operator!=(const char* lhs, const String& rhs);
    friend bool operator<(const String& lhs, const String& rhs);
    friend bool operator<(const String& lhs, const char* rhs);
    friend bool operator<(const char* lhs, const String& rhs);
    friend bool operator>(const String& lhs, const String& rhs);
    friend bool operator>(const String& lhs, const char* rhs);
    friend bool operator>(const char* lhs, const String& rhs);
    friend bool operator<=(const String& lhs, const String& rhs);
    friend bool operator<=(const String& lhs, const char* rhs);
    friend bool operator<=(const char* lhs, const String& rhs);
    friend bool operator>=(const String& lhs, const String& rhs);
    friend bool operator>=(const String& lhs, const char* rhs);
    friend bool operator>=(const char* lhs, const String& rhs);

    friend String operator+(const String& lhs, const String& rhs);
    friend String operator+(const char* lhs, const String& rhs);
    friend String operator+(char lhs, const String& rhs);
    friend String operator+(const String& lhs, const char* rhs);
    friend String operator+(const String& lhs, char rhs);
    friend String operator+(String&& lhs, const String& rhs);
    friend String operator+(const String& lhs, String&& rhs);
    friend String operator+(String&& lhs, String&& rhs);
    friend String operator+(const char* lhs, String&& rhs);
    friend String operator+(char lhs, String&& rhs);
    friend String operator+(String&& lhs, const char* rhs);
    friend String operator+(String&& lhs, char rhs);

public:
    String() = default;
    ~String() = default;
    String(const String&) = default;
    String(String&&) = default;
    String& operator=(const String&) = default;
    String& operator=(String&&) = default;

    explicit String(const std::string& stdStr) : mImpl(stdStr) {}
    explicit String(std::string&& stdStr) : mImpl(std::move(stdStr)) {}

    const char& operator[](uint64 pos) const { return mImpl[pos]; }
    char& operator[](uint64 pos) { return mImpl[pos]; }

    String& operator=(char c);
    String& operator=(const char* c);

    String& operator+=(char c);
    String& operator+=(const char* c);
    String& operator+=(const String& str);

public:
    uint64 Size() const noexcept { return mImpl.size(); }

    bool Empty() const noexcept { return mImpl.empty(); }

private:
    std::string mImpl;
};

inline bool operator==(const String& lhs, const String& rhs) { return lhs.mImpl == rhs.mImpl; }
inline bool operator==(const String& lhs, const char* rhs) { return lhs.mImpl == rhs; }
inline bool operator==(const char* lhs, const String& rhs) { return lhs == rhs.mImpl; }
inline bool operator!=(const String& lhs, const String& rhs) { return lhs.mImpl != rhs.mImpl; }
inline bool operator!=(const String& lhs, const char* rhs) { return lhs.mImpl != rhs; }
inline bool operator!=(const char* lhs, const String& rhs) { return lhs != rhs.mImpl; }
inline bool operator<(const String& lhs, const String& rhs) { return lhs.mImpl < rhs.mImpl; }
inline bool operator<(const String& lhs, const char* rhs) { return lhs.mImpl < rhs; }
inline bool operator<(const char* lhs, const String& rhs) { return lhs < rhs.mImpl; }
inline bool operator>(const String& lhs, const String& rhs) { return lhs.mImpl > rhs.mImpl; }
inline bool operator>(const String& lhs, const char* rhs) { return lhs.mImpl > rhs; }
inline bool operator>(const char* lhs, const String& rhs) { return lhs > rhs.mImpl; }
inline bool operator<=(const String& lhs, const String& rhs) { return lhs.mImpl <= rhs.mImpl; }
inline bool operator<=(const String& lhs, const char* rhs) { return lhs.mImpl < rhs; }
inline bool operator<=(const char* lhs, const String& rhs) { return lhs < rhs.mImpl; }
inline bool operator>=(const String& lhs, const String& rhs) { return lhs.mImpl >= rhs.mImpl; }
inline bool operator>=(const String& lhs, const char* rhs) { return lhs.mImpl >= rhs; }
inline bool operator>=(const char* lhs, const String& rhs) { return lhs >= rhs.mImpl; }
inline String operator+(const String& lhs, const String& rhs) { return String{lhs.mImpl + rhs.mImpl}; }
inline String operator+(const char* lhs, const String& rhs) { return String(lhs + rhs.mImpl); }
inline String operator+(char lhs, const String& rhs) { return String(lhs + rhs.mImpl); }
inline String operator+(const String& lhs, const char* rhs) { return String(lhs.mImpl + rhs); }
inline String operator+(const String& lhs, char rhs) { return String(lhs.mImpl + rhs); }
inline String operator+(String&& lhs, const String& rhs) { return std::move(lhs += rhs); }
inline String operator+(const String& lhs, String&& rhs) { return std::move(rhs += lhs); }
inline String operator+(String&& lhs, String&& rhs) { return std::move(lhs += rhs); }
inline String operator+(const char* lhs, String&& rhs) { return std::move(rhs += lhs); }
inline String operator+(char lhs, String&& rhs) { return std::move(rhs += lhs); }
inline String operator+(String&& lhs, const char* rhs) { return std::move(lhs += rhs); }
inline String operator+(String&& lhs, char rhs) { return std::move(lhs += rhs); }

#endif  // WORKENGINE_STRING_H
