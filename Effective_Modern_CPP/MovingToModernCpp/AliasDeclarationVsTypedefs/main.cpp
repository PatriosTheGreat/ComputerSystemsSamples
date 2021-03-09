#include <iostream>
#include <list>

struct Point { };
template<typename T> // MyAllocList<T>::type
struct MyAllocList { // is synonym for
    typedef std::list<T> type; // std::list<T,
}; // MyAlloc<T>>

template<typename T> // MyAllocList<T>
using C11MyAllocList = std::list<T>; // is synonym for

/*
    template <class T>
    using remove_const_t = typename remove_const<T>::type;
    template <class T>
    using remove_reference_t = typename remove_reference<T>::type;
    template <class T>
    using add_lvalue_reference_t =
    typename add_lvalue_reference<T>::type;
*/

int main() {
    MyAllocList<Point>::type lw; // client code c98

    C11MyAllocList<Point> c11; // C11+
}