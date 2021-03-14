#include <iostream>
#include <memory>
#include <vector>

struct Point {};

void makeLogEntry(Point *pw) {

}

auto loggingDel = [](Point *pw) // custom deleter
{
    makeLogEntry(pw);
    delete pw;
};

std::unique_ptr< // deleter type is
Point, decltype(loggingDel)> // part of ptr type
upw(new Point, loggingDel);

std::shared_ptr<Point> // deleter type is not
spw(new Point, loggingDel); // part of ptr type

class Widget: public std::enable_shared_from_this<Widget> {
public:
    void process() { processedWidgets.emplace_back(shared_from_this()); } // auto cast to shared
  std::vector<std::shared_ptr<Widget>> processedWidgets;  
};

int main() {
    auto customDeleter1 = [](Point *pw) { }; // custom deleters,
    auto customDeleter2 = [](Point *pw) { }; // each with a
    // different type
    std::shared_ptr<Point> pw1(new Point, customDeleter1);
    std::shared_ptr<Point> pw2(new Point, customDeleter2);
    std::vector<std::shared_ptr<Point>> vpw{ pw1, pw2 };


    auto pw = new Point;
    std::shared_ptr<Point> spw1(pw, loggingDel); // create control
    // block for *pw
    std::shared_ptr<Point> spw2(pw, loggingDel); // create 2nd
    // control block
    // for *pw!
}