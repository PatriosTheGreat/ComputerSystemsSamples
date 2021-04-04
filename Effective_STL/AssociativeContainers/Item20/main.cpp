#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

struct StringPtrLess : public binary_function<const string*, const string*, bool> { //class
    bool operator()(const string *ps1, const string *ps2) const
    {
        return *ps1 < *ps2;
    }
};

void print(const string *ps) // print to cout the
{                            // object pointed to
    cout << *ps << endl; //by ps
}

struct Dereference {
    template <typename T>
    const T& operator()(const T *ptr) const
    {
        return *ptr;
    }
};

int main() {
    set<string*> ssp; // ssp = "set of string ptrs"
    ssp.insert(new string("Anteater"));
    ssp.insert(new string("Wombat"));
    ssp.insert(new string("Lemur"));
    ssp.insert(new string("Penguin"));

    for (set<string*>::const_iterator i = ssp.begin();  i != ssp.end(); ++i)
        cout << *i << endl; 

    
    for (set<string*>::const_iterator i = ssp.begin(); i != ssp.end(); ++i)
        cout << **i << endl;


    set<string*, less<string*>, allocator<string*> > ssp_full;

    typedef set<string*, StringPtrLess> StringPtrSet;
    StringPtrSet ssp_correct; // create a set of strings and order
                              // them as defined by StringPtrLess
                              // insert the same four strings as
                              // before

    
    ssp_correct.insert(new string("Anteater"));
    ssp_correct.insert(new string("Wombat"));
    ssp_correct.insert(new string("Lemur"));
    ssp_correct.insert(new string("Penguin"));

    
    for (StringPtrSet::const_iterator i = ssp_correct.begin(); i != ssp_correct.end(); ++i)
        cout << **i << endl;

    for_each(ssp_correct.begin(), ssp_correct.end(), print);

    transform( ssp_correct.begin(), ssp_correct.end(), // "transform" each  element in ssp by dereferencing it, writing the results to cout
        ostream_iterator<string>(cout, "\n"),
        Dereference());
}