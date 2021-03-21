#include <iostream>

#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <vector>

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}


template<typename T>
void func(T&& param) {
    std::cout << "Call func with param: " << type_name<decltype(param)>() << std::endl;
}

class Widget { };
Widget widgetFactory() { // function returning rvalue
    return Widget();    
}

int main() {
    Widget w; // a variable (an lvalue)
    func(w);  // call func with lvalue; T deduced
              // to be Widget&
    func(widgetFactory()); // call func with rvalue; T deduced
                           // to be Widget

    Widget &other = w;
    func(other);

    Widget &&rOther = std::move(w);
    func(rOther);
}