#include <iostream>

class Point {
public:

private:
    Point(const Point& ); // not defined
    Point& operator=(const Point& ); // not defined
};

class PointC11 {
public:
    PointC11(const PointC11& ) = delete;
    PointC11& operator=(const PointC11&) = delete;
};

bool isLucky(int number) {
    return true;
}

bool isLucky(char) = delete; // reject chars
bool isLucky(bool) = delete; // reject bools
bool isLucky(double) = delete; // reject

template<typename T>
void processPointer(T* ptr) {
    std::cout << "Process ptr: " << ptr << std::endl; 
}

template<>
void processPointer<void>(void*) = delete;

template<>
void processPointer<char>(char*) = delete;

template<>
void processPointer<const void>(const void*) = delete;
template<>
void processPointer<const char>(const char*) = delete; // We can't do this in class in C++98

int main() {
    // Point a; Error
    // Point b(a); Error 
    // Point c = a; Error

    // PointC11 d; Error
    // PointC11 e(d); Error
    // PointC11 f = d; Error
    isLucky(11);
    // isLucky('a');  Error
    // isLucky(true); Error
    // isLucky(3.5f); Error
}