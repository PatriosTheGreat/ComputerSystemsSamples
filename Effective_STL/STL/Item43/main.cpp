#include <iostream>
#include <list>
#include <algorithm>
#include <deque>

using namespace std;

class Widget {
public:
    void redraw() const {
        cout << "redraw called for " << this << endl;
    }
};

int main() {
    list<Widget> lw;
    lw.push_back(Widget());
    lw.push_back(Widget());

    for (list<Widget>::iterator i = lw.begin(); i != lw.end(); ++i) {
        i->redraw();
    }

    for_each(lw.begin(), lw.end(), mem_fun_ref(&Widget::redraw));
}