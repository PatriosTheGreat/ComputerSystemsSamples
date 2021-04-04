#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>
#include <deque>

using namespace std;

int main() {
    typedef deque<int> IntDeque;                //convenience typedefs
    typedef IntDeque::iterator Iter;
    typedef IntDeque::const_iterator ConstIter;
    ConstIter ci;                               // ci is a const_iterator

    // Iter i(ci);                              // error! no implicit conversion from
                                                // const_iterator to iterator

    // Iter i(const_cast<Iter>(ci));            // still an error! can't cast a
                                                // const_iterator to an iterator

    IntDeque d;
    Iter i(d.begin());
    advance(i, distance<ConstIter>(i, ci)); // move i up to where ci is
}