#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Old API
void doSomething(const int* pints, size_t numlnts) {

}

int main() {
    // Correct way to invoke old API
    set<int> intSet;
    vector<int> v(intSet.begin(), intSet.end());
    if (!v.empty()) doSomething(&v[0], v.size());
}