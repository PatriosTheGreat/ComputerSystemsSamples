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
#include <deque>

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

bool f(const std::string& w) {

}

struct Point {
    int x, y;
};

template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i)
    -> decltype(c[i])
{
    return c[i];
}

template<typename Container, typename Index>
auto c14AuthAndAccess(Container& c, Index i)
{
    return c[i];
}

template<typename Container, typename Index>
decltype(auto) c14AssignAuthAndAccess(Container& c, Index i)
{
    return c[i];
}

template<typename Container, typename Index>
decltype(auto) c14AssignAuthAndAccessRR(Container&& c, Index i)
{
    return std::forward<Container>(c)[i];
}

template<typename Container, typename Index>
auto c11AssignAuthAndAccess(Container&& c, Index i)
-> decltype(std::forward<Container>(c[i]))
{
    return std::forward<Container>(c)[i];
}

std::deque<std::string> makeStringDeque() {
    std::deque<std::string> d = { "1", "2", "3" }; 
    return d;
}

decltype(auto) f1() {
    int x = 0;
    return x;
}

decltype(auto) f2() {
    int x = 0;
    return (x);
}

int main() {
    const int i = 0;
    std::cout << "x is " << type_name<decltype(i)>() << std::endl;

    std::cout << "f is: " << type_name<decltype(f)>() << std::endl;

    std::cout << "Point.x is: " << type_name<decltype(Point::x)>() << std::endl;
 
    std::string a = "123";
    auto c = authAndAccess(a, 1);
    std::cout << "c is " << type_name<decltype(c)>() << std::endl;

    auto c14 = c14AuthAndAccess(a, 1);
    std::cout << "c14 is " << type_name<decltype(c14)>() << std::endl;

    authAndAccess(a, 1) = 'd';
    std::cout << a << std::endl;


    // c14AuthAndAccess(a, 2) = 'e'; don't compile:  expression is not assignable
    
    c14AssignAuthAndAccess(a, 2) = 'e';
    std::cout << a << std::endl;


    Point p;
    const Point &cp = p;
    auto myPoint1 = cp;
    decltype(auto) myPoint2 = cp;
    
    std::cout << "myPoint1 is " << type_name<decltype(myPoint1)>() << std::endl;
    std::cout << "myPoint2 is " << type_name<decltype(myPoint2)>() << std::endl;


    // auto s = c14AssignAuthAndAccess(makeStringDeque(), 1);
    /*
     note: candidate function [with Container = std::deque<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > >, Index = int] not viable: expects an l-value for 1st argument
        decltype(auto) c14AssignAuthAndAccess(Container& c, Index i)
    */
    std::cout << "f1 is " << type_name<decltype(f1())>() << std::endl;

    std::cout << "f2 is " << type_name<decltype(f2))>() << std::endl;

    return 0;
}