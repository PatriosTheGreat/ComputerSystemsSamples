#include <iostream>

class Widget {
public:
    Widget(Widget&& rhs); // move constructor
    Widget& operator=(Widget&& rhs); // move assignment operator
};

class Widget {
public:
~Widget(); // user-declared dtor
Widget(const Widget&) = default; // behavior is OK
Widget& // default copy assign
operator=(const Widget&) = default; // behavior is OK
};
class Base {
public:
    virtual ~Base() = default; // make dtor virtual

    Base(Base&&) = default; // support moving
    Base& operator=(Base&&) = default;
    Base(const Base&) = default; // support copying
    Base& operator=(const Base&) = default;
};

int main() {

}