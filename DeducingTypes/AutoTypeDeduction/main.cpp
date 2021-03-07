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

void someFunc(int a, double b) {
    std::cout << "some func" << std::endl;
}

template <typename T>
void f(T param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}


template <typename T>
void nf(std::initializer_list<T> param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

/*
auto createInitList() {
    return { 1, 2, 3 };
}
Compile error: cannot deduce return type from initializer list
*/

int main() {
    auto x = 27;    
    const auto cx = x;
    const auto &rx = x;
    
    std::cout << "x is " << type_name<decltype(x)>() << std::endl;
    std::cout << "cx is " << type_name<decltype(cx)>() << std::endl;
    std::cout << "rx is " << type_name<decltype(rx)>() << std::endl;


    auto &&uref1 = x;
    auto &&uref2 = cx;
    auto &&ured3 = 27;

    std::cout << "uref1 is " << type_name<decltype(uref1)>() << std::endl;
    std::cout << "uref2 is " << type_name<decltype(uref2)>() << std::endl;
    std::cout << "ured3 is " << type_name<decltype(ured3)>() << std::endl;

    const char name[] = "R. N. Briggs";

    auto arr1 = name;
    auto& arr2 = name;

    std::cout << "arr1 is " << type_name<decltype(arr1)>() << std::endl;
    std::cout << "arr2 is " << type_name<decltype(arr2)>() << std::endl;

    auto func1 = someFunc;
    auto& func2 = someFunc;
    
    std::cout << "func1 is " << type_name<decltype(func1)>() << std::endl;
    std::cout << "func2 is " << type_name<decltype(func2)>() << std::endl;


    auto x1 = 27;
    auto x2(27);
    auto x3 = { 27 };
    auto x4{ 27 };

    std::cout << "x1 is " << type_name<decltype(x1)>() << std::endl;
    std::cout << "x2 is " << type_name<decltype(x2)>() << std::endl;
    std::cout << "x3 is " << type_name<decltype(x3)>() << std::endl;
    std::cout << "x4 is " << type_name<decltype(x4)>() << std::endl;
    

    // f({1, 2, 3}); compilation error: candidate template ignored: couldn't infer template argument 'T'

    nf({1, 2 ,3});


    std::vector<int> v;
    auto resetV = [&v] (const auto& newVal) { v = newVal };

    // resetV({ 1, 2, 3 }); compilation error: couldn't infer template argument 'newVal:auto'
}