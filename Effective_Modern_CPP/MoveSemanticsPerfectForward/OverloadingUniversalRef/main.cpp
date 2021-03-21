#include <iostream>
#include <set>
#include <chrono>

void log(std::chrono::system_clock::time_point now, const std::string& name) {

}

std::multiset<std::string> names; // global data structure

/*
void logAndAdd(const std::string& name)
{
    auto now = // get current time
    std::chrono::system_clock::now();
    log(now, "logAndAdd"); // make log entry
    names.emplace(name); // add name to global data
} // structure; see Item 42


std::string petName("Darla");
logAndAdd(petName); // pass lvalue std::string
logAndAdd(std::string("Persephone")); // pass rvalue std::string
logAndAdd("Patty Dog"); // pass string literal
// for info on emplace
*/
template<typename T>
void logAndAdd(T&& name)
{
    auto now = // get current time
    std::chrono::system_clock::now();
    log(now, "logAndAdd"); // make log entry
    names.emplace(std::forward<T>(name)); // add name to global data

    std::cout << "universal ref overload" << std::endl;
} // structure; see Item 42
// for info on emplace

std::string nameFromIdx(int idx) { // return name
                                   // corresponding to idx
    return "Darla";
}
void logAndAdd(int idx) // new overload
{
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
    names.emplace(nameFromIdx(idx));

    std::cout << "int overload" << std::endl;
}
/*
class Person {
public:
    template<typename T>
    explicit Person(T&& n) // perfect forwarding ctor;
        : name(std::forward<T>(n)) {} // initializes data member
    explicit Person(int idx) // int ctor
        : name(nameFromIdx(idx)) {}

    Person(const Person& rhs); // copy ctor
                            // (compiler-generated)
    Person(Person&& rhs); // move ctor
                      // (compiler-generated)

private:
    std::string name;
};


// Person p("Nancy");
// auto cloneOfP(p); // create new Person from p;
                    // this won't compile! With T&&
*/

int main() {
    std::string petName("Darla");

    logAndAdd(petName); // as before, copy
                                   // lvalue into multiset
    logAndAdd(std::string("Persephone")); // move rvalue instead
                                                     // of copying it
    logAndAdd("Patty Dog"); // create std::string
                                       // in multiset instead
                                       // of copying a temporary
                                       // std::string

    logAndAdd(petName); // as before, these
    logAndAdd(std::string("Persephone")); // calls all invoke
    logAndAdd("Patty Dog"); // the T&& overload
    logAndAdd(22); // calls int overload
    // Person p("Nancy");
    // auto cloneOfP(p); // create new Person from p;
                    // this won't compile! With T&&
    // short nameIdx = 1;
    // logAndAdd(nameIdx); // error!

}