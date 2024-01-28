#include <bits/stdc++.h>

using namespace std;

class Test {
public:
    Test() = delete;
    Test(string str) : tt(str) {
        cout << tt << " is constructed via `string` \n";
    }
    Test(const Test& other) {
        tt = other.tt;
        cout << tt << " is constructed via `Test&` \n";
    }
    ~Test() {
        cout << tt << " is destructed \n";
    }
    Test& operator=(const Test& other) {
        cout << tt << " is assigned by " << other.tt << '\n';
        tt = other.tt;
        return *this;
    }
private:
    string tt;
};

void mark_times() {
    static int time = 1;
    cout << "Mark: " << time << '\n';
    ++time;
}

Test fun (Test t) {
    mark_times();
    cout << "** next gonna return **\n";
    return t;
}

int main() {
    Test test1("Hello");
    mark_times();
    Test test2("World");
    mark_times();
    test1 = fun(test2);
    mark_times();
    cout << "final test\n";
    test2 = fun(test2);
    mark_times();
    
    return 0;
}