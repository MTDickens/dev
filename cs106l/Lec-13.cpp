#include <vector>
#include <iostream>

using namespace std;

class Test {
public:    
    Test() : count(0) {}
    Test(const Test& other) noexcept {
        this->count = other.count + 1;
    }
    ~Test() {
        // default
    }
    void operator() () {
        cout << count << ' ';
    }
    
private:
    int count;
};

int main() {
    vector<Test> t;
    t.push_back(Test());
    t.emplace_back();
    for (auto i : t) {
        i();
    }
    
    return 0;
}