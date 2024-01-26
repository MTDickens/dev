#include <bits/stdc++.h>

using namespace std;

class StringVector
{
private:
    vector<string> data;

public:
    StringVector() = default;

    StringVector &operator+=(const string &str);
    StringVector &operator+=(const StringVector &vec);

    // Note: don't use `string& operator[] const (const int& index);`
    // Since `const` modifier doesn't allow you to return a
    // non-const reference to a member variable
    string &operator[](const int &index);

    int size();
};

int StringVector::size()
{
    return data.size();
}

// Member function style
StringVector &StringVector::operator+=(const string &str)
{
    data.push_back(str);
    return *this;
}

StringVector &StringVector::operator+=(const StringVector &vec)
{
    data.insert(data.end(), vec.data.cbegin(), vec.data.cend());
    return *this;
}

// Non-member function style

string &StringVector::operator[](const int &index)
{
    return data[index];
}

int main()
{
}