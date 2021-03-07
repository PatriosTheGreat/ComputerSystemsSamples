#include <iostream>

#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>

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

template <typename T>
void f(T& param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

template <typename T>
void cf(const T& param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

template <typename T>
void pf(T* param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

template <typename T>
void uf(T&& param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

template <typename T>
void nf(T param) {
    std::cout << __PRETTY_FUNCTION__  << std::endl;
    std::cout << type_name<decltype(param)>() << std::endl;
}

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
    return N;
}

void someFunc(int a, double b) {
    std::cout << "some func" << std::endl;
}

int main() {

    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x);
    f(cx);
    f(rx);

    cf(x);
    cf(cx);
    cf(rx);

    const int *px = &x;

    pf(&x);
    pf(px);

    uf(x);
    uf(cx);
    uf(rx);
    uf(27);

    nf(x);
    nf(cx);
    nf(rx);

    const char* const ptr = "Pointer";

    nf(ptr);
    f(ptr);


    const char name[] = "J. P. Briggs";
    const char *ptrToName = name;

    f(name);

    int keyVals[] = { 1, 2, 3, 4, 5, 6 };
    int mappedVals[arraySize(keyVals)];
    std::array<int, arraySize(keyVals)> mappedValsArr;

    std::cout << "Functions" << std::endl;
    nf(someFunc);
    f(someFunc);
}