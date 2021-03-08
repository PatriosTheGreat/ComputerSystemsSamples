#include <iostream>
#include <vector>

class Point {
public:
    Point(int i, bool b) {
        std::cout << "int and bool" << std::endl;
    }

    Point(int i, double d) {
        std::cout << "int and double" << std::endl;
    }

    Point(std::initializer_list<long double> il) {
        std::cout << "initialize_list" << std::endl;
    }
private:
    int x{ 0 };
    int y = 0;
    // int z(0); Error
};

class Point2 {
public:
    Point2(int i, double d) {
        std::cout << "int and double" << std::endl;
    }

    Point2(std::initializer_list<bool> il) {
        std::cout << "initialize_list" << std::endl;
    }
private:
    int x{ 0 };
    int y = 0;
    // int z(0); Error
};

int main() {
    std::vector<int> v{ 1, 3, 5 };

    double x, y, z;

    // int sum1{ x + y + z }; error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]

    int sum2(x + y + z);

    Point w1(10, true); // uses parens and, as before,
    // calls first ctor
    Point w2{10, true}; // uses braces, but now calls
    // std::initializer_list ctor
    // (10 and true convert to long double)
    Point w3(10, 5.0); // uses parens and, as before,
    // calls second ctor
    Point w4{10, 5.0}; // uses braces, but now calls
    // std::initializer_list ctor
    // (10 and 5.0 convert to long double)

    // Point2 w22{10, 5.0}; Error can not conver double to bool
}