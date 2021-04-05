#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
    list<double> Id;
    Id.push_back(-1.0);
    Id.push_back(1.0);
    Id.push_back(0.1);
    double sum = accumulate(Id.begin(), Id.end(), 1.0);

    cout << "sum: " << sum << endl;

    cout << "The sum of the ints on the standard input is: " // print the sum of
        << accumulate( istream_iterator<int>(cin), // the ints in cin
                        istream_iterator<int>(),
                        0) << endl;
}