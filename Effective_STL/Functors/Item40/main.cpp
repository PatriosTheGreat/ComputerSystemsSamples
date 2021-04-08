#include <iostream>
#include <functional>
#include <deque>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

class Widget { };

bool isInteresting(const Widget *pw) {
    return false;
}

int main() {
    list<Widget*> widgetPtrs;

    // list<Widget*>::iterator i =
    //     find_if(widgetPtrs.begin(), widgetPtrs.end(), not1(isInteresting)); //error! won't compile

    list<Widget*>::iterator i =
        find_if(widgetPtrs.begin(), widgetPtrs.end(),
        not1(ptr_fun(isInteresting))); //fine

    if ( i != widgetPtrs.end()) {
    }
}