#include <boost/type_index.hpp>
#include <iostream>

template<typename T>
void f(const T& param)
{
    using std::cout;
    using boost::typeindex::type_id_with_cvr;
    // show T
    cout << "T = " << type_id_with_cvr<T>().pretty_name() << '\n';
    // show param's type
    cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << '\n';
}


struct Point {
    int x, y;
};
int main() {
    Point p;
    const Point &cp = p;
    auto myPoint1 = cp;
    decltype(auto) myPoint2 = cp;
    
    f(myPoint1);
    f(myPoint2);
}