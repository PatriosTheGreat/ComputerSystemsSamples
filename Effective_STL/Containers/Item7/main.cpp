#include <vector>
#include <algorithm>
#include <iostream>

class Widget {};

void doSomething()
{
    std::vector<Widget*> vwp;
    for (int i = 0; i < 42; ++i)
        vwp.push_back(new Widget);
} //Widgets are leaked here!


void doSomethingCorrect() {
    std::vector<Widget*> vwp;
    for (int i = 0; i < 42; ++i)
        vwp.push_back(new Widget);

    for (std::vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i) {
        delete *i;
    }
}

struct DeleteObject { // templatization and base
                      // class removed here
    template<typename T>
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

void doSomethingForEach() {
    std::vector<Widget*> vwp;
    for (int i = 0; i < 42; ++i)
        vwp.push_back(new Widget);
    
    std::for_each(vwp.begin(), vwp.end(), DeleteObject());
}


int main() {
    doSomething();
    doSomethingCorrect();
    doSomethingForEach();
}