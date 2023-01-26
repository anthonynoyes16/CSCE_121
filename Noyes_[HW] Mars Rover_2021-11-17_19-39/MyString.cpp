// TODO: Implement this source file
#include "MyString.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <limits>

MyString::MyString() : size_array(0), capacity_array(1), str(new char[1]{'\0'})
{
}

MyString::MyString(const MyString &hold) : size_array(hold.size()), capacity_array(hold.capacity()), str(new char[hold.capacity()]{})
{
    for (unsigned int i = 0; i < size_array; i++)
    {
        str[i] = hold.data()[i];
    }
}

MyString::MyString(const char *s) : size_array(0), capacity_array(1), str(new char[1]{})
{
    int i = -1;
    do
    {
        i++;
        str[i] = s[i];
        size_array++;
        if (size_array == capacity_array)
        {
            capacity_array += 1;
            char *hold = new char[capacity_array]{};
            for (unsigned int j = 0; j < size_array; j++)
            {
                hold[j] = str[j];
            }
            delete[] str;
            str = hold;
        }
    } while (s[i] != '\0');
    size_array -= 1;
}

MyString::~MyString()
{
    delete[] str;
}

void MyString::resize(size_t n)
{
    if (n >= size_array)
    {
        capacity_array = n + 1;
        char *hold = new char[capacity_array]{};
        for (unsigned int i = 0; i < size_array; i++)
        {
            hold[i] = str[i];
        }
        hold[size_array] = '\0';
        delete[] str;
        str = hold;
    }
    else if (n < size_array)
    {
        capacity_array = n + 1;
        size_array = n;
        char *hold = new char[capacity_array]{};
        for (unsigned int i = 0; i < size_array; i++)
        {
            hold[i] = str[i];
        }
        hold[size_array] = '\0';
        delete[] str;
        str = hold;
    }
}

size_t MyString::capacity() const noexcept
{
    return capacity_array;
}

size_t MyString::size() const noexcept
{
    return size_array;
}

size_t MyString::length() const noexcept
{
    return size_array;
}

const char *MyString::data() const noexcept
{
    return str;
}

bool MyString::empty() const noexcept
{
    if (size_array == 0)
    {
        return true;
    }
    return false;
}

const char &MyString::front() const
{
    return str[0];
}

const char &MyString::at(size_t pos) const
{
    if (pos >= size_array)
    {
        throw std::out_of_range("out of bounds access");
    }
    return str[pos];
}

void MyString::clear() noexcept
{
    char *hold = new char[1]{'\0'};
    size_array = 0;
    capacity_array = 1;
    delete[] str;
    str = hold;
}

MyString &MyString::operator=(const MyString &hold)
{
    size_array = hold.size();
    capacity_array = hold.capacity();
    delete[] str;
    str = new char[capacity_array]{};
    for (unsigned int i = 0; i < hold.capacity(); i++)
    {
        str[i] = hold.data()[i];
    }
    return *this;
}

MyString &MyString::operator+=(const MyString &hold)
{
    resize(size_array + hold.size());
    for (unsigned int j = size_array; j < capacity_array; j++)
    {
        str[j] = hold.data()[j - size_array];
    }
    size_array += hold.size();
    str[size_array] = '\0';
    return *this;
}

size_t MyString::find(const MyString &hold, size_t pos) const noexcept
{
    for (unsigned int i = pos; i <= size_array; i++)
    {
        for (unsigned int j = 0; j < hold.size(); j++)
        {
            if (i + j > size_array)
            {
                break;
            }
            if (str[i + j] != hold.data()[j])
            {
                break;
            }
            else if (j == hold.size() - 1)
            {
                return i;
            }
        }
    }
    return -1;
}

std::ostream &operator<<(std::ostream &os, const MyString &hold)
{
    os << hold.data();
    return os;
}

bool operator== (const MyString& lhs, const MyString& rhs) noexcept 
{
    if (lhs.size() != rhs.size()) 
    {
        return false;
    }
    for (unsigned int i = 0; i < lhs.size(); i++) {
        if (lhs.data()[i] != rhs.data()[i]) 
        {
            return false;
        }
    }
    return true;
}

MyString operator+ (const MyString& lhs, const MyString& rhs) 
{
    char* hold = new char[lhs.size() + rhs.size()] {};
    for (unsigned int i = 0; i < lhs.size(); i++)
    {
        hold[i] = lhs.data()[i];
    }
    for (unsigned int j = 0; j < rhs.size(); j++) 
    {
        hold[j + lhs.size()] = rhs.data()[j];
    }
    return MyString(hold);
}