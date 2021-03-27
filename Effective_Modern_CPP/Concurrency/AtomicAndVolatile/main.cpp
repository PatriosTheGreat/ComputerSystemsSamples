#include <iostream>
#include <atomic>
#include <thread>
#include <future>

int main() {
    {
        std::atomic<int> ai(0); // initialize ai to 0
        ai = 10; // atomically set ai to 10
        std::cout << ai; // atomically read ai's value
        ++ai; // atomically increment ai to 11

        --ai; // atomically decrement ai to 10
    }

    // In reallity undefined parallel work
    {
        volatile int vi(0); // initialize vi to 0
        vi = 10; // set vi to 10
        std::cout << vi; // read vi's value
        ++vi; // increment vi to 11
        --vi; // decrement vi to 10
    }

    {
        std::atomic<int> ac(0); // "atomic counter"
        volatile int vc(0); // "volatile counter"
    }

    {
        volatile std::atomic<int> vai; // operations on vai are
                                       // atomic and can't be
                                        // optimized away
    }
}