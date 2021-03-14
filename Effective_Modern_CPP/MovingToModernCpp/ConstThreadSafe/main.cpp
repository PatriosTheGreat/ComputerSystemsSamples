#include <iostream>
#include <vector>

class Polynomial {
public:
    using RootsType = std::vector<double>;
    RootsType roots() const
    {
        if (!rootsAreValid) { // if cache not valid
            // store them in rootVals
            rootsAreValid = true;
        }
        return rootVals;
    }

private:
    mutable bool rootsAreValid{ false }; // see Item 7 for info
    mutable RootsType rootVals{}; // on initializers
};

int main() {

}