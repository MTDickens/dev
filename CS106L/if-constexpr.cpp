#include <iostream>
#include <string>

using namespace std;

template <typename T>
void test (T a) {
    if constexpr (false) {
        a << 2;
    }
}

int main() {
    string i = "1", j = "2";
    test(i);

    return 0;
}