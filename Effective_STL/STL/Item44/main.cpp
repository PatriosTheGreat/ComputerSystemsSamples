#include <iostream>
#include <list>
#include <algorithm>
#include <deque>
#include <set>

using namespace std;

int main() {
    set<int> s;
    for (int i = 0; i < 100000; i++) {
        s.insert(i);
    }

    // This is much faster
    {
        set<int>::iterator i = s.find(727); // use find member
        if (i != s.end()) {
            cout << "Cant find 727" << endl;
        }
    }
    
    // Then this
    {
        set<int>::iterator i = find(s.begin(), s.end(), 727); // use find algorithm
        if(i != s.end()) {

        }
    }
}