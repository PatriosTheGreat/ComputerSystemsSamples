#include <iostream>
#include <memory>

struct Investment { };
struct Stock: public Investment { };
struct Bond: public Investment { };
struct RealEstate: public Investment { };

void makeLogEntry(Investment* pInvestment) {

}

auto delInvmt = [](Investment* pInvestment) // custom
{ // deleter
    makeLogEntry(pInvestment); // (a lambda
    delete pInvestment; // expression)
};

template<typename... Ts> // revised
std::unique_ptr<Investment, decltype(delInvmt)> // return type
makeInvestment(Ts&&... params)
{
    std::unique_ptr<Investment, decltype(delInvmt)> // ptr to be
    pInv(nullptr, delInvmt); // returned
    if ( /* a Stock object should be created */ )
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( /* a Bond object should be created */ )
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( /* a RealEstate object should be created */ )
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }
    return pInv;
}



template<typename... Ts>
auto makeInvestmentC14(Ts&&... params) // C++14
{
    auto delInvmt = [](Investment* pInvestment) // this is now
    { // inside
        makeLogEntry(pInvestment); // makedelete
        pInvestment; // Investment
    };

    std::unique_ptr<Investment, decltype(delInvmt)> // as
    pInv(nullptr, delInvmt); // before
    if ( true ) // as before
    {
    pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( true ) // as before
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( true ) // as before
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }
    return pInv; // as before
}


auto delInvmt1 = [](Investment* pInvestment) // custom
{ // deleter
    makeLogEntry(pInvestment); // as
    delete pInvestment; // stateless
}; // lambda


template<typename... Ts> // return type
std::unique_ptr<Investment, decltype(delInvmt1)> // has size of
makeInvestment(Ts&&... args); // Investment*
void delInvmt2(Investment* pInvestment) // custom
{ // deleter
    makeLogEntry(pInvestment); // as function
    delete pInvestment;
}


template<typename... Ts> // return type has
std::unique_ptr<Investment, // size of Investment*
void (*)(Investment*)> // plus at least size
makeInvestment(Ts&&... params); // of function pointer!


int main() {

}