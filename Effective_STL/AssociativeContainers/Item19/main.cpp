#include <iostream>
#include <chrono>

using namespace std;

class Widget {
public:
    friend bool operator==(const Widget& lhs, const Widget& rhs) {
        // code that ignores the lastAccessed field
    }
private:
    time_t lastAccessed;
};

struct CiStringCompare : public binary_function<string, string, bool> { // see Item 40 for info on
    //this base class
    bool operator()(const string& lhs,
                    const string& rhs) const
    {
        return false; // ciStringCompare(lhs, rhs); // see Item 35 for how
                                    } //ciStringCompare is
                                    // implemented
};

int main() {

}