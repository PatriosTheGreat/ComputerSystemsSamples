#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;


struct StringPtrGreaterIncorrect :                                       // highlights show how
                        public binary_function<const string*,   // this code was changed
                                                const string*,  // from page 89. Beware,
                                                bool> {         // this code is flawed!
    bool operator()(const string *ps1, const string *ps2) const
    {
        return !(*ps1 <*ps2);                                   //just negate the old test;
    }                                                           // this is incorrect!
};


struct StringPtrGreater :                                       // highlights show how
                        public binary_function<const string*,   // this code was changed
                                                const string*,  // from page 89. Beware,
                                                bool> {         // this code is flawed!
    bool operator()(const string *ps1, const string *ps2) const
    {
        return *ps1 > *ps2;                                     //return whether *ps2
    }                                                           //precedes *ps1 (i.e., swap
                                                                //the order of the
};                                                              // operands)

int main() {

}