#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<bool> v;
    // bool *pb = &v[0]; // initialize a bool* with the address of
                      // what vector<bool>::operator[] returns
                      // error! the expression on tne right is
                      // of type vector<bool>::reference*,
                      // not bool*
                      // vector<bool> is a special container  which use bitset
}