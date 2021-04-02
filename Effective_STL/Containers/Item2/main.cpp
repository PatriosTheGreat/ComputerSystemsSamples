#include <iostream>
#include <vector>
#include <algorithm>

class Widget { 
    friend bool operator==( const Widget &w1, const Widget &w2) {
        return false;
    }
};

int main() {
    // Bad
    std::vector<Widget> vw;
    Widget bestWidget;

    std::vector<Widget>::iterator i = // find a Widget with the
        find(vw.begin(), vw.end(), bestWidget); // same value as bestWidget

    // Good
    typedef std::vector<Widget> WidgetContainer;
    typedef WidgetContainer::iterator WCIterator;
    WidgetContainer vw2;
    Widget bestWidget2;

    WCIterator i2 = find(vw2.begin(), vw2.end(), bestWidget2);
    return 0;
}