#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int transmogrify(int x) {
    return 2*x;
} // this function produces

int main() {
    {
        vector<int> values;
        values.reserve(10);
        for (int i = 0; i < 10; i++) {
            values.push_back(i);
        }

        vector<int> results; // apply transmogrify to
        // transform( values.begin(), values.end(), // each object in values,
        //             results.end(), // appending the return
        //            transmogrify); // values to results; this
                                    //code has a bug!

        transform(values.begin(), values.end(), //each object in values,
                back_inserter(results), //inserting the return
                transmogrify);

        for(int v : results) {
            cout << v << " ";
        }

        cout << endl;
    }

    // Now try to override values.

    vector<int> values;
    values.reserve(10);
    for (int i = 0; i < 10; i++) {
        values.push_back(i);
    }

    vector<int> results;
    for (int i = 0; i < 10; i++) {
        results.push_back(i);
    }

    if ( results.size() < values.size()){ //make sure results is at
        results.resize(values.size()); // least as big as values is
    }

    transform(values.begin(), values.end(), // overwrite the first
              results.begin(), // values.size() elements of
              transmogrify); // results

    
    for(int v : results) {
        cout << v << " ";
    }

    cout << endl;
}