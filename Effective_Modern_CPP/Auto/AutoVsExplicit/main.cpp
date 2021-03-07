#include <iostream>

template<typename It> // algorithm to dwim ("do what I mean")
    void dwim(It b, It e) // for all elements in range from
{ // b to e
    while (b != e) {
        typename std::iterator_traits<It>::value_type
        currValue = *b;
    }
}

int main() {
    int x1; //  no error uninitialized

    // auto x2; -- can't compile
    auto x3 = 0;

    auto lambda = [](const auto& p1, const auto& p2) { return *p1 < *p2; };

    int a = 4;
    int b = 5;
    std::cout << lambda(&a, &b) << std::endl;

    float c = 4.0;
    float d = 5.0;
    std::cout << lambda(&c, &d) << std::endl;

    std::cout << lambda(&a, &c) << std::endl;
}