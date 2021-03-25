#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <memory>

using FilterContainer =
    std::vector<std::function<bool(int)>>;
    
double computeSomeValue1() {
    return 0.0;
}

double computeSomeValue2() {
    return 1.0;
}

int computeDivisor(double a, double b) {
    return 1.0;
}

void addDivisorFilter()
{
    FilterContainer filters;

    auto calc1 = computeSomeValue1();
    auto calc2 = computeSomeValue2();
    int divisor = computeDivisor(calc1, calc2);
    // filters.emplace_back( // danger!
    //     [&divisor](int value) { return value % divisor == 0; } // ref to
    // ); // divisor  will  dangle!

    filters.emplace_back( // now
        [=](int value) { return value % divisor == 0; } // divisor
    ); // can't
    // dangle
}

// This is a case when we can closure variable by reference.
template<typename C>
void workWithContainer(const C& container)
{
    auto calc1 = computeSomeValue1(); // as above
    auto calc2 = computeSomeValue2(); // as above
    auto divisor = computeDivisor(calc1, calc2); // as above
    using ContElemT = typename C::value_type; // type of
    // elements in
    // container
    using std::begin; // for
    using std::end; // genericity;
    // see Item 13
    if (std::all_of( // if all values
        begin(container), end(container), // in container
        [&](const ContElemT& value) // are multiples
        { return value % divisor == 0; }) // of divisor...
        ) {
    // if (std::all_of(begin(container), end(container),
    // [&](const auto& value) // C++14
    // { return value % divisor == 0; }))
    } else {
    } // isn't...
}


class Widget {
public:
    // ctors, etc.
    void addFilter(); // add an entry to filters

private:
    int divisor; // used in Widget's filter
    FilterContainer filters;
};

void Widget::addFilter() {
    auto divisorCopy = divisor;
    filters.emplace_back(
        [divisorCopy](int value) { return value % divisorCopy == 0; }
    );

    filters.emplace_back( // C++14:
        [divisor = divisor](int value) // copy divisor to closure
        { return value % divisor == 0; } // use the copy
    );
}

FilterContainer filters; // as before

void doSomeWork()
{
    auto pw = // create Widget; see
        std::make_unique<Widget>(); // Item 21 for
        // std::make_unique
    pw->addFilter(); // add filter that uses
        
}

void addDivisorFilter()
{
    static auto calc1 = computeSomeValue1(); // now static
    static auto calc2 = computeSomeValue2(); // now static
    static auto divisor = // now static
    computeDivisor(calc1, calc2);
    filters.emplace_back(
        [=](int value) // captures nothing!
        { return value % divisor == 0; } // refers to above static
    );
    ++divisor; // modify divisor
}

int main() {
    filters.emplace_back(
        [](int value) { return value % 5 == 0; }
    );


}