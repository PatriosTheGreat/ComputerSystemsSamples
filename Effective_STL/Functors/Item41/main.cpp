#include <iostream>
#include <functional>
#include <deque>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class Widget {
public:
    void test() {
        cout << "Widget testing w: " << this << endl;
    }
};

void test(Widget& w) {
    cout << "Testing w: " << &w << endl;
}

int main() {
    vector<Widget> vw;
    vw.push_back(Widget());
    vw.push_back(Widget());

    for_each(vw.begin(), vw.end(), test);          // Call #1
    for_each(vw.begin(), vw.end(), ptr_fun(test)); // compiles and behaves
                                                   // like Call #1 above
    // for_each(vw.begin(), vw.end(), &Widget::test); // wont compile Call #2

    list<Widget*> lpw; // lpw holds pointers to widgets
    lpw.push_back(new Widget());
    lpw.push_back(new Widget());
    // for_each(lpw.begin(), lpw.end(), &Widget::test); //Call #3 (also won't compile) Call #3

    for_each(lpw.begin(), lpw.end(),
        mem_fun(&Widget::test)); // this will now compile
}