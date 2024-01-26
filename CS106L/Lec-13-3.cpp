#include <iostream>
#include <utility>

using namespace std;

class Test {
public:
    Test(Test &t)
    {
        i = t.i;
        cout << "constructed!\n";
    }
    Test() : i(0) { }
private:
    int i;
};

int main () {
    Test t;
    std::move(t);
}