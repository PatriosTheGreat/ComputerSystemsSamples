#include <iostream>
#include <bitset>


int main() {
    float a = 0;

    for (int i = 0; i < 10; i++) {
        a += 0.1;
    }

    std::cout << (a > 1) ? "true" : "false" << std::endl;
}