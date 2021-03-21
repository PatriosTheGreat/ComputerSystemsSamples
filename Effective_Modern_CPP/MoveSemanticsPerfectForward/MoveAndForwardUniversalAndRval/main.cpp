#include <iostream>
#include <memory>

struct SomeDataStructure { };

class Widget {
public:
    Widget(Widget&& rhs) // rhs definitely refers to an
        : name(std::move(rhs.name)),
            p(std::move(rhs.p))
    { }
    
    template<typename T>
    void setName(T&& newName) // newName is
    { name = std::forward<T>(newName); } // universal reference

    template<typename T> // text is
    void setSignText(T&& text) // univ. reference
    {
        // sign.setText(text); // use text, but
        // don't modify it
        // auto now = // get current time
        //    std::chrono::system_clock::now();
        // signHistory.add(now,
        //    std::forward<T>(text)); // conditionally cast
    }

private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p;
};

/*

Matrix // by-value return
operator+(Matrix&& lhs, const Matrix& rhs)
{
    lhs += rhs;
    return std::move(lhs); // move lhs into
}
Matrix // as above
operator+(Matrix&& lhs, const Matrix& rhs)
{
    lhs += rhs;
    return lhs; // copy lhs into
} // return value

template<typename T>
Fraction // by-value return
reduceAndCopy(T&& frac) // universal reference param
{
    frac.reduce();
    return std::forward<T>(frac); // move rvalue into return
} // value, copy lvalue
*/