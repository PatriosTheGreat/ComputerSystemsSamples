#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int ciCharCompare(char c1, char c2)                    // case-insensitively compare chars
{                                                      // c1 and c2, returning -1 if c1 < c2,
                                                       // 0 if c1==c2, and 1 if c1 > c2
    int Ic1 = tolower(static_cast<unsigned char>(c1)); // see below for
    int Ic2 = tolower(static_cast<unsigned char>(c2)); // info on these

    if (Ic1 < Ic2) return -1;
    if (Ic1 > Ic2) return 1;
    return 0;
}

int ciStringCompareImpl(const string& s1, //see below for
                        const string& s2); // implementation

bool ciCharLess(char c1, char c2) {
    return tolower(static_cast<unsigned char>(c1)) < tolower(static_cast<unsigned char>(c2));
}

int ciStringCompare(const string& s1, const string& s2)
{
    return lexicographical_compare(s1.begin(), s1.end(), //see below for
                                    s2.begin(), s2.end(), // a discussion of
                                    ciCharLess); //this algorithm
}

int ciStringCompareImpl(const string& s1, const string& s2)
{
    typedef pair<string::const_iterator, // PSCI = "pair of
    string::const_iterator> PSCI; // string::const_iterator"
    PSCI p= mismatch( //see below for an
                    s1.begin(), s1.end(), //explanation of why
                    s2.begin(), //we need not2;see
                    not2(ptr_fun(ciCharCompare))); //Item 41 for why we
    // need ptr_fun
    if (p.first== s1.end()) { //if true, either s1 and
        if (p.second == s2.end()) return 0; // s2 are equal or
        else return -1; //s1 is shorter than s2
    }
    return ciCharCompare(*p.first, *p.second);  // the relationship of the
}                                               // strings is the same as
                                                // that of the
                                                // mismatched chars

int main() {

}