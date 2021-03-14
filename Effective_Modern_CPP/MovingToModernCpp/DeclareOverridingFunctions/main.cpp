#include <iostream>
#include <vector>

class Widget {
public:
    void doWork() & {
        std::cout << "rvalue do work" << std::endl;
    }
    // only when *this is an lvalue
    void doWork() && {
        std::cout << "lvalue do work" << std::endl;
    }
};

Widget makeWidget() {
    return Widget();
}

class Widget2 {
public:
    using DataType = std::vector<double>; // see Item 9 for
    DataType& data() & { return values; }
    DataType data() && { return std::move(values); }
private:
    DataType values;
};

Widget2 makeWidget2() {
    return Widget2();
}

int main() {
    Widget w;
    w.doWork(); 
    makeWidget().doWork();


    Widget2 w2;
    auto val1 = w2.data(); // calls lvalue overload for Widget::data, copy-constructs vals1

    auto val2 = makeWidget2().data(); // calls rvalue overload for Widget::data, move-constructs vals2
}