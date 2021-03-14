#include <iostream>
#include <vector>

template <class C>
auto cbegin(const C& container)->decltype(std::begin(container)) // C++11 way
{
    return std::begin(container);
}

int main() {
    std::vector<int> values;
    // auto it = std::find(values.cbegin(), values.cend(), 1983); Wont compile

    // values.insert(it, 1998);
}