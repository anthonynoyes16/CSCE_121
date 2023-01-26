// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString {
private:
    unsigned int size_array;
    unsigned int capacity_array;
    char* str = new char[size_array] {};
public:
    MyString();
    MyString (const MyString& str);
    MyString (const char* s);
    ~MyString();
    void resize (size_t n);
    size_t capacity() const noexcept;
    size_t size() const noexcept;
    size_t length() const noexcept;
    const char* data() const noexcept;
    bool empty() const noexcept;
    const char& front() const; 
    const char& at(size_t pos) const;
    void clear() noexcept;
    MyString& operator= (const MyString& str);
    MyString& operator+= (const MyString& str);
    size_t find (const MyString& str, size_t pos = 0) const noexcept;
};
std::ostream& operator<< (std::ostream& os, const MyString& str);
MyString operator+ (const MyString& lhs, const MyString& rhs);
bool operator== (const MyString& lhs, const MyString& rhs) noexcept;
#endif