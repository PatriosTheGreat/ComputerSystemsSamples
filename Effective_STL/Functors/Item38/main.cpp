#include <iostream>
#include <functional>
#include <deque>
#include <algorithm>

using namespace std;

class DoSomething : public unary_function<int, void> { // Item 40 explains base class
public:
    void operator()(int x) {
        cout << "Do with " << x << endl; 
    }
};

class Widget {

};

template<typename T>
class BPFC : public unary_function<T, void> { 
public:
    virtual void operator()(const T& val) const {
        pImpl->operator()(val);
    }
private:
    BPFCImpl<T> *pImpl;
};

template<typename T> //new implementation class
class BPFCImpl {    
public:
    virtual ~BPFCImpl();
    virtual void operator()(const T& val) const;
    friend class BPFC<T>; // let BPFC access the data

private:
    Widget w; // all the data that used to
    int x; //be in BPFC are now here
};

int main() {
    typedef deque<int>::iterator DequeIntIter; //convenience typedef
    deque<int> di;
    DoSomething d;

    di.push_back(1);

    for_each<DequeIntIter, // call for_each with type
            DoSomething&>(di.begin(), // parameters of DequeIntIter
                          di.end(), //and DoSomething&;
                          d);
}