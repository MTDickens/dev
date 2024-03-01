#include <cstring>
#include <iostream>

#define MAX_LENGTH 1024

class MyString
{
public:
    MyString(const char *c_str)
    {
        length = strlen(c_str);
        _str = new char[MAX_LENGTH];
        strncpy(_str, c_str, MAX_LENGTH);
    }

    MyString(MyString &&other) : _str(other._str), length(other.length) {}
    MyString(const MyString &other)
    {
        length = other.length;
        _str = new char[MAX_LENGTH];
        strncpy(_str, other._str, MAX_LENGTH);
    }

    MyString &operator=(const char *c_str)
    {
        length = strlen(c_str);
        strncpy(_str, c_str, MAX_LENGTH);
        return *this;
    }
    MyString &operator=(MyString &&other)
    {
        _str = other._str;
        length = other.length;
        return *this;
    }
    MyString &operator=(const MyString &other)
    {
        if (_str != nullptr)
            delete _str;
        strncpy(_str, other._str, MAX_LENGTH);
        length = other.length;
        return *this;
    }

    const char *c_str()
    {
        return _str;
    }

    const int size()
    {
        return length;
    }

    friend std::ostream &operator<<(std::ostream &os, MyString str);

private:
    char *_str;
    unsigned int length;
};

std::ostream &operator<<(std::ostream &os, MyString str)
{
    return (os << str._str);
}

int main()
{
    MyString str1("Hello");
    std::cout << "str1: " << str1 << '\n';
    MyString str2(str1);
    str2 = "World";
    std::cout << "str2: " << str2 << '\n';
    std::cout << "Uncorrupted str1: " << str1 << '\n';
    MyString str3(std::move(str1));
    str3 = "This is corrupted :(";
    std::cout << "Corrupted str1: " << str1 << '\n';

    return 0;
}