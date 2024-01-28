#include <iostream>
using namespace std;

class Test {
public:    
    Test() : count(0) {}
    Test(const Test& other) noexcept {
        this->count = other.count + 10000;
    }
    ~Test() {
        // default
    }
    Test& operator=(const Test& other) {
        this->count = other.count + 1;
        return *this;
    }
    Test& operator() () {
        cout << count << ' ';
        return *this;
    }
    
private:
    int count;
};

Test test_non_reference(Test test) {
    test();
    return test;
}

Test& test_reference(Test &test) {
    test();
    return test;
}

int main()
{
    Test test;
    test();
    test = test_non_reference(test)();
    test();
    test = test_reference(test)();
    test();
    return 0;
}