#include <iostream>
#include <array>

constexpr int powc11(int base, int exp) noexcept // C++ 11
{
    return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

constexpr int pow(int base, int exp) noexcept // C++14
{
    auto result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}

class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal) {}
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    constexpr void setX(double newX) noexcept // C++14
    { x = newX; }
    constexpr void setY(double newY) noexcept // C++14
    { y = newY; }
private:
    double x, y;
};

constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return { (p1.xValue() + p2.xValue()) / 2, // call constexpr
            (p1.yValue() + p2.yValue()) / 2 }; // member funcs
}

// return reflection of p with respect to the origin (C++14)
constexpr Point reflection(const Point& p) noexcept
{
    Point result; // create non-const Point
    result.setX(-p.xValue()); // set its x and y values
    result.setY(-p.yValue());
    return result; // return copy of it
}

int main() {
    int sz; // non-constexpr variable
    // constexpr auto arraySize1 = sz; // error! sz's value not known at compilation
    // std::array<int, sz> data1; // error! same problem
    constexpr auto arraySize2 = 10; // fine, 10 is a
    const auto arraySize = sz; // fine, arraySize isconst copy of sz
    // std::array<int, arraySize> data; // error! arraySize's value not known at compilation

    constexpr auto numConds = 5; // # of conditions
    std::array<int, pow(3, numConds)> results;

    constexpr Point p1(9.4, 27.7); // fine, "runs" constexpr
    // ctor during compilation
    constexpr Point p2(28.8, 5.3); // also fine

    
    constexpr auto mid = midpoint(p1, p2); // init constexpr
                                           // object w/result of constexpr function

    constexpr Point p1(9.4, 27.7); // as above
    constexpr Point p2(28.8, 5.3);
    constexpr auto mid = midpoint(p1, p2);
    constexpr auto reflectedMid = // reflectedMid's value is
        reflection(mid); // (-19.1 -16.5) and known
    // during compilation
} 