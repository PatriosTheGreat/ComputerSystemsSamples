#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

class Widget {
public:
    Widget() : weight_(0) { }

    Widget(double weight) : weight_(weight) {}

    Widget& operator=(double weight) {
        weight_ = weight;
        return *this;
    }

private:
    double weight_;
};

template<typename MapType, // type of map
         typename KeyArgType, // see below for why
         typename ValueArgtype> // KeyArgType and
// ValueArgtype are type
typename MapType::iterator efficientAddOrUpdate(MapType& m,
                                                const KeyArgType& k,
                                                const ValueArgtype& v)
{
    typename MapType::iterator Ib =      // find where k is or should
                m.lower_bound(k);        // be; see page 7 for why

                                         // "typename" is needed
                                         // here
    if(lb != m.end() &&                  // if Ib points to a pair
        !(m.key_comp()(k, lb->first))) { // whose key is equiv to k...
        lb->second = v;                  // update the pair's value
        return Ib;                       // and return an iterator
    }                                    // to that pair
    else{
        typedef typename MapType::value_type MVT;
        return m.insert(lb, MVT(k, v));  // add pair(k, v) to m and
    }                                    // return an iterator to the
}

int main() {
    map<int, Widget> m;
    // m[1] = 1.50;
    // This is equevalent to:
    typedef map<int, Widget> IntWidgetMap; 
    pair<IntWidgetMap::iterator, bool> result = // create new map
    m.insert(IntWidgetMap::value_type(1, Widget())); // entry with key 1
                                                    //and a default-
                                                    // constructed value
                                                    // object; see below
                                                    //for a comment on
                                                    // value_type
    result.first->second = 1.50; // assign to the
                                // newly-constructe

    // Above code is not effective. Better do the followed:
    m.insert(IntWidgetMap::value_type(1, 1.50));

    m[2] = 3.67;
    m[3] = 10.5;
    m[4] = 45.8;
    m[5] = 0.0003;
}