#include <iostream>
#include <list>
#include <algorithm>
#include <deque>
#include <set>
#include <vector>
#include <chrono>

using namespace std;

int main() {
    vector<int> v;
    int x, y;

    // This works, but unreadable
    v.erase(
        remove_if(find_if(v.rbegin(), v.rend(),
                            bind2nd(greater_equal<int>(), y)).base(),
                            v.end(),
                            bind2nd(less<int>(), x)),
        v.end());

    // MUCH easier to read
    typedef vector<int>::iterator VecIntIter;
    //initialize rangeBegin to the first element in v that's greater than
    //or equal to the last occurrence of y. If no such element exists,
    // initialize rangeBegin to v.begin()

    VecIntIter rangeBegin = find_if(v.rbegin(), v.rend(),
                                    bind2nd(greater_equal<int>(), y)).base();
    // from rangeBegin to v.end(), erase everything with a value less than x
    v.erase(remove_if(rangeBegin, v.end(), bind2nd(less<int>(), x)), v.end());
}