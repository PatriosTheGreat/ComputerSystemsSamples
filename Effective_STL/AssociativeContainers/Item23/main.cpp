#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;
typedef pair<string, int> Data; // type held in the "map"

// in this example
class DataCompare {                                  // class for comparison
public:                                              // functions
    bool operator()(const Data& lhs,                 // comparison func
                    const Data& rhs) const           // for sorting
    {
        return keyLess(lhs.first, rhs.first);        // keyLess is below
    }

    bool operator()(const Data& lhs,                 // comparison func
                    const Data::first_type& k) const // for lookups
    {                                                // (form 1)
        return keyLess(lhs.first, k);
    }

    bool operator()(const Data::first_type& k,       // comparison func
                    const Data& rhs) const           // for lookups
    {                                                // (form 2)
        return keyLess(k, rhs.first);
    }
private:
    bool keyLess(const Data::first_type& k1,         // the "real"
    const Data::first_type& k2) const                // comparison
    {                                                // function
        return k1 < k2;
    }
};

int main() {
    vector<Data> vd;
    sort(vd.begin(), vd.end(), DataCompare());
    string s;
    if (binary_search(vd.begin(), vd.end(), s, DataCompare())) {  
    }
    vector<Data>::iterator i =
        lower_bound(vd.begin(), vd.end(), s,
                    DataCompare());


    pair<vector<Data>::iterator,
        vector<Data>::iterator> range =
                equal_range(vd.begin(), vd.end(), s, DataCompare());
    
    if (range.first != range.second) { }

    sort(vd.begin(), vd.end(), DataCompare());
}