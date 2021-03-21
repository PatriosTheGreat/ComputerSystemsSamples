#include <iostream>
#include <chrono>

// MOVE

/*
template<typename T> // in namespace std
typename remove_reference<T>::type&&
move(T&& param)
{
    using ReturnType = // alias declaration;
    typename remove_reference<T>::type&&; // see Item 9
    return static_cast<ReturnType>(param);
}
*/
class Annotation {
public:
    explicit Annotation(const std::string text)
        : value(std::move(text)) { } // Copy, not move because text is const!

    std::string value;
};

/*
class string { // std::string is actually a
public: // typedef for std::basic_string<char>
…
string(const string& rhs); // copy ctor -- this actuallu will be called
string(string&& rhs); // move ctor -- no const 
…
};
*/

// FORWARD

class Widget { 
public:

    Widget(Widget&& rhs)
        : s(std::move(rhs.s))
    { ++moveCtorCalls; }

/*
Widget(Widget&& rhs) // unconventional,
: s(std::forward<std::string>(rhs.s)) // undesirable
{ ++moveCtorCalls; } // implementation
the same
*/
private:
    static std::size_t moveCtorCalls;
    std::string s;
};

void process(const Widget& lvalArg) { // process lvalues 
    std::cout << "Process lvalue" << std::endl;
}

void process(Widget&& rvalArg) { // process rvalues
    std::cout << "Process rvalue" << std::endl;
}

template<typename T> // template that passes
void logAndProcess(T&& param) // param to process
{
    auto now = // get current time
        std::chrono::system_clock::now();
    std::cout << "Calling 'process'" << std::chrono::system_clock::to_time_t(now) << std::endl; 
    // makeLogEntry("Calling 'process'", now);
    process(std::forward<T>(param));
}


int main() {
    Widget w;
    logAndProcess(w); // call with lvalue
    logAndProcess(std::move(w)); // call with rvalue
}