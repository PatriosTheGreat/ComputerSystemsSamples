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


void f(const std::vector<int>& v) {
    std::cout << "vector" << std::endl;
}

void f(std::size_t val) {
    std::cout << "size_t" << std::endl;
}

int processVal(int value) {
    std::cout << " Process val: " << value << std::endl;
}

int processVal(int value, int priority) {
    std::cout << "Process val: " << value << " priority: " << priority << std::endl;
}

void f(int (*pf)(int)) { // pf = "processing function"
    std::cout << "processing function" << std::endl;
}
/*
void f(int pf(int)) {
    std::cout << "same" << std::endl;
}
*/
template<typename... T>
void fwd(T&&... param) // accept any argument
{
    f(std::forward<T>(param)...); // forward it to f
}

class Widget {
public:
    static const std::size_t MinVals = 28; // MinVals' declaration

};

struct IPv4Header {
    std::uint32_t version:4,
                  IHL:4,
                  DSCP:6,
                  ECN:2,
                  totalLength:16;
};

int main() {
    // Braced initializers
    f({ 1, 2, 3 }); // fine, "{1, 2, 3}" implicitly
                    // converted to std::vector<int>

    // fwd({ 1, 2, 3 }); // error! doesn't compile

    auto il = { 1, 2, 3 }; // il's type deduced to be
                           // std::initializer_list<int>
    fwd(il); // fine, perfect-forwards il to f


    // Declaration-only integral static const data members
    std::vector<int> widgetData;
    widgetData.reserve(Widget::MinVals); // use of MinVals

    f(Widget::MinVals); // fine, treated as "f(28)"
    // fwd(Widget::MinVals); // error! shouldn't link



    // Overloaded function names and template names
    f(processVal); // fine
    // fwd(processVal); // error! which processVal?

    using ProcessFuncType = // make typedef;
        int (*)(int); // see Item 9
    ProcessFuncType processValPtr = processVal;

    fwd(processValPtr);



    // Bitfields
    IPv4Header h;
    f(h.totalLength); // fine
    // fwd(h.totalLength); // error!
    auto length = static_cast<std::uint16_t>(h.totalLength);
    fwd(length);
}