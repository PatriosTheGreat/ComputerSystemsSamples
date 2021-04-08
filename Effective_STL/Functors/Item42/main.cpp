#include <iostream>
#include <functional>
#include <deque>
#include <algorithm>
#include <multiset>
#include <list>

using namespace std;

class Widget {
public:
    Widget(size_t weight, size_t maxSpeed) : weight_(weight), maxSpeed_(maxSpeed) { }

    size_t weight() const {
        return weight_;
    }

    size_t maxSpeed() const {
        return maxSpeed_;
    }
    
private:
    size_t weight_, maxSpeed_;
};

bool operator<(const Widget& lhs, const Widget& rhs) {
    return lhs.weight() < rhs.weight();
}

// NEVER DO LIKE THIS
/*
template<>
struct std::less<Widget> :
    public std::binary_function<Widget, Widget, bool> 
{ 
    bool operator()(const Widget& lhs, const Widget& rhs) const
    {
        return lhs.maxSpeed() < rhs.maxSpeed();
    }
};
*/

// Do this
struct MaxSpeedCompare:
    public binary_function<Widget, Widget, bool> 
{
    bool operator()(const Widget& lhs, const Widget& rhs) const
    {
        return lhs.maxSpeed() < rhs.maxSpeed();
    }
};

int main() {
    // Sorted by max speed
    multiset<Widget, MaxSpeedCompare> widgets;
    // Sorted by weight
    multiset<Widget> widgets2;
}