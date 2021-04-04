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
    {
        vector<int> v;
        v.reserve(5);
        for(int i = 1;i <= 5;++i){ //put 1-5 in the vector
            v.push_back(i);
        }

        vector<int>::reverse_iterator ri = // make ri point to the 3
            find(v.rbegin(), v.rend(), 3);

        vector<int>::iterator i(ri.base()); // make i the same as ri's base
    }

    vector<int> v;
    v.reserve(5);
    for(int i = 1;i <= 5;++i){ //put 1-5 in the vector
        v.push_back(i);
    }
    vector<int>::reverse_iterator ri = // as above, make ri point to the 3
        find(v.rbegin(), v.rend(), 3);
    //v.erase(--ri.base()); // attempt to erase at the position
                            // preceding ri.base(); for a vector,
                            // this will typically nor compile

    v.erase((++ri).base()); // Will compile with all implementations
}