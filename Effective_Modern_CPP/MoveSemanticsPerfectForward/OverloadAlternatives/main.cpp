#include <iostream>
#include <chrono>
#include <set>

void log(std::chrono::system_clock::time_point now, const std::string& name) {

}

std::multiset<std::string> names; // global data structure

// Tag despatch
std::string nameFromIdx(int idx) { // return name
                                   // corresponding to idx
    return "Darla";
}

template<typename T> // non-integral
void logAndAddImpl(T&& name, std::false_type) // argument:
{ // add it to
    auto now = std::chrono::system_clock::now(); // global data
    log(now, "logAndAdd"); // structure
    names.emplace(std::forward<T>(name));

    std::cout << "Universal ref overload" << std::endl;
}

template<typename T>
void logAndAdd(T&& name);

void logAndAddImpl(int idx, std::true_type) // integral
{ // argument: look
    std::cout << "int overload" << std::endl;
    logAndAdd(nameFromIdx(idx)); // up name and
} // call logAndAdd
// with it

template<typename T>
void logAndAdd(T&& name)
{
    logAndAddImpl(std::forward<T>(name),
        std::is_integral<typename std::remove_reference<T>::type>()
    ); // not quite correct
}

// Enable if
class Person {
public:
    template<
        typename T,
        typename = typename std::enable_if<
                !std::is_base_of<Person,
                    typename std::decay<T>::type
                    >::value
                    &&
                !std::is_integral<std::remove_reference_t<T>>::value
            >::type
    >
    explicit Person(T&& n)
        : name(std::forward<T>(n)) { 
        static_assert(
            std::is_constructible<std::string, T>::value,
            "Parameter n can't be used to construct a std::string"
        );
        std::cout << "Perfect forward" << std::endl;
    }

    explicit Person(int idx) // ctor for integral args
    : name(nameFromIdx(idx))
    { }
private:
    std::string name;
};

class SpecialPerson: public Person {
public:
    SpecialPerson(const SpecialPerson& rhs) // copy ctor; calls
    : Person(rhs) // base class
        {  } // forwarding ctor!
    SpecialPerson(SpecialPerson&& rhs) // move ctor; calls
    : Person(std::move(rhs)) // base class
        {  } // forwarding ctor!
};

int main() {
    // Tag
    std::string petName("Darla");
    logAndAdd(petName); // as before, these
    logAndAdd(std::string("Persephone")); // calls all invoke
    logAndAdd("Patty Dog"); // the T&& overload
    logAndAdd(22); // calls int overload

    short nameIdx = 1;
    logAndAdd(nameIdx); // error!


    // Enable if
    Person p("123");

    Person copyToP(p);

    Person pn(1);

    // Person pc16(u"Konrad Zuse"); // "Konrad Zuse" consists of
                                    // characters of type const char16_t
}