#include <iostream>
#include <list>
#include <algorithm>
#include <deque>
#include <set>
#include <vector>
#include <chrono>

using namespace std;
inline
bool doubleGreater(double d1, double d2)
{
    return d1 > d2;
}

int main() {
    vector<double> v;
    v.push_back(1.0f);
    v.push_back(-2.0f);
    v.push_back(5.0f);
    v.push_back(0.0f);

    // THIS IS MUCH FASTER
    sort(v.begin(), v.end(), greater<double>());

    // THAN THIS since inline wont work
    sort(v.begin(), v.end(), doubleGreater);
}