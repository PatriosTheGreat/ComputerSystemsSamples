#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v; // create a vector<int> and fill it with
    v.reserve(10); //the values 1-10. (See Item 14 for an
    for (int i = 1; i <= 10; ++i) { //explanation of the reserve call.)
        v.push_back(i);
    }
    cout << v.size() << endl; //prints 10
    v[3] = v[5] = v[9] = 99; // set 3 elements to 99
    remove(v.begin(), v.end(), 99); // remove all elements with value 99
    cout << v.size() << endl; // still prints 10!

    v.erase(remove(v.begin(), v.end(), 99), v.end());
    cout << v.size() << endl; //now returns 7
}