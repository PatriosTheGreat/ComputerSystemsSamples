#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <iterator>

class Widget {};

Widget w(); // This is a function declaration, not var.

int main() {
    std::ifstream dataFile("ints.dat");
    std::list<int> dataFunc(std::istream_iterator<int>(dataFile), // warning! this doesn't do
                            std::istream_iterator<int>());        // what you think it does


    std::list<int> data((std::istream_iterator<int>(dataFile)), // note new parens
                        std::istream_iterator<int>());          // around first argument
                                                                // to list's constructor

    
    return 0;
}