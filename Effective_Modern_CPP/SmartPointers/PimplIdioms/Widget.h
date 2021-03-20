
// We need to include these two headers

/*
class Widget { // in header "widget.h"
public:
    Widget() {
    }
private:
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3; // Gadget is some user-
}; // defined type
*/

#include <memory>

class WidgetPimpl { // in header "widget.h"
public:
    WidgetPimpl();
    ~WidgetPimpl(); // declaration only
    WidgetPimpl(WidgetPimpl&& rhs); // right idea,
    WidgetPimpl& operator=(WidgetPimpl&& rhs); // wrong code!

    WidgetPimpl(const WidgetPimpl& rhs); // declarations
    WidgetPimpl& operator=(const WidgetPimpl& rhs); // only
private:
    struct Impl;
    std::shared_ptr<Impl> pImpl; // std::shared_ptr
}; // defined type
