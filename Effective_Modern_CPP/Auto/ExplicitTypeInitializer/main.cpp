#include <iostream>
#include <vector>

struct Point {
};

std::vector<bool> get_bools() {
    return std::vector<bool>({ true });
}

void print(bool val) {
    std::cout << "val: " << val << std::endl; 
}

int main() {
    auto val = get_bools()[0];
    print(val);

    bool val2  = get_bools()[0];
    print(val2);

    auto val3 = static_cast<bool>(get_bools()[5]);
    print(val3);
}