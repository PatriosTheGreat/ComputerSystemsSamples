#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <memory>



int main() {
    auto f =
        [](auto&& param)
        {
            return
                func(normalize(std::forward<decltype(param)>(param)));
        };
}