#include <iostream>
#include <functional>
#include <deque>
#include <algorithm>
#include <vector>

using namespace std;

class Widget { };

class BadPredicate: public unary_function<Widget, bool> {
public:
    BadPredicate() : timesCalled(0) { }
    
    bool operator()(const Widget&)
    {
        return ++timesCalled == 3;
    }

private:
    size_t timesCalled;
};

int main() {
    vector<Widget> vw;

    // This code looks quite reasonable, but with many STL implementations,
    // it will eliminate not just the third element from vw,
    // it will also eliminate the sixth!
    vw.erase(remove_if(vw.begin(),
                       vw.end(),
                       BadPredicate()),
             vw.end());
}