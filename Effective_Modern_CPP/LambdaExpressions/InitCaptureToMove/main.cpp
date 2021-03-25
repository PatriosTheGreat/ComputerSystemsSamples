#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <memory>

class Widget { // some useful type
public:
    bool isValidated() const {
        return true;
    }

    bool isProcessed() const {
        return true;
    }

    bool isArchived() const {
        return true;
    }

private:
};

class IsValAndArch { // "is validated
public: // and archived"
    using DataType = std::unique_ptr<Widget>;
    
    explicit IsValAndArch(DataType&& ptr) // Item 25 explains
        : pw(std::move(ptr)) {} // use of std::move
    
    bool operator()() const
        { return pw->isValidated() && pw->isArchived(); }
private:

    DataType pw;
};

void main() {
    auto pw = std::make_unique<Widget>();

    auto func = 
        [pw = std::move(pw)] // init data mbr
        { return pw->isValidated() // in closure w/
                && pw->isArchived(); }; // std::move(pw)

    auto func2 = IsValAndArch(std::make_unique<Widget>());



    std::vector<double> data;

    auto funcC11 = [data = std::move(data)] // C++14 init capture
    { /* uses of data */ };

    auto funcC14 =
        std::bind( // C++11 emulation
            [](const std::vector<double>& data) // of init capture
                { /* uses of data */ },
            std::move(data)
        );


    auto funcC11Mutable =
        std::bind( // C++11 emulation
            [](std::vector<double>& data) mutable // of init capture
                { /* uses of data */ }, // for mutable lambda
            std::move(data)
        );

    auto funcC11Saple = std::bind(
        [](const std::unique_ptr<Widget>& pw)
            { return pw->isValidated()
                    && pw->isArchived(); },
        std::make_unique<Widget>()
    );
}