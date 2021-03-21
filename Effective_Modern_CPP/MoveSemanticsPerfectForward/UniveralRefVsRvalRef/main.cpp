#include <iostream>

class Widget {

};

void f(Widget&& param) { // rvalue reference

}

template<typename T>
void f(std::vector<T>&& param) { // rvalue reference

}

template<typename T>
void f(T&& param) { // not rvalue reference

}

/*
template<class T, class Allocator = allocator<T>> // from C++
class vector { // Standards
public:
void push_back(T&& x); -- rvalue
…
};
*/

/*
template<class T, class Allocator = allocator<T>> // still from
class vector { // C++
public: // Standards
template <class... Args>
void emplace_back(Args&&... args); -- universal reference
…
};
*/

int main() {

    Widget&& var1 = Widget(); // rvalue reference
    auto&& var2 = var1; // not rvalue reference

/*
auto timeFuncInvocation =
[](auto&& func, auto&&... params) // C++14
{
    start timer;
    std::forward<decltype(func)>(func)( // invoke func
        std::forward<decltype(params)>(params)... // on params
    );
    stop timer and record elapsed time;
};
*/
}