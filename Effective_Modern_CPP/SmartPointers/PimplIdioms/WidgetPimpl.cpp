#include "Widget.h" // in impl. file "widget.cpp"
#include "Gadget.h"
#include <string>
#include <vector>

struct WidgetPimpl::Impl { // definition of Widget::Impl
    std::string name; // with data members formerly
    std::vector<double> data; // in Widget
    Gadget g1, g2, g3;
};

WidgetPimpl::WidgetPimpl() // allocate data members for
: pImpl(std::make_shared<Impl>()) // this Widget object
{}

WidgetPimpl::~WidgetPimpl() = default;

WidgetPimpl::WidgetPimpl(WidgetPimpl&& rhs) = default; // defini-
WidgetPimpl& WidgetPimpl::operator=(WidgetPimpl&& rhs) = default; // tions

WidgetPimpl::WidgetPimpl(const WidgetPimpl& rhs) // copy ctor
: pImpl(std::make_shared<Impl>(*rhs.pImpl))
{}

WidgetPimpl& WidgetPimpl::operator=(const WidgetPimpl& rhs) // copy operator=
{
    *pImpl = *rhs.pImpl;
    return *this;
}