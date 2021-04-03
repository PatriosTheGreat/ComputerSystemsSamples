#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(1000);
    for (int i = 1; i <= 1000; ++i) v.push_back(i);
}