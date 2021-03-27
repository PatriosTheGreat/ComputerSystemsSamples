#include <iostream>
#include <thread>
#include <future>
#include <vector>

class Widget { // Widget objects might
public:        // block in their dtors
private:
    std::shared_future<double> fut;
};

int calcValue() { // func to run
    std::cout << "calc value" << std::endl;
}

int main() {
    // this container might block in its dtor, because one or more
    // contained futures could refer to a shared state for a non-
    // deferred task launched via std::async
    std::vector<std::future<void>> futs;

    { // begin block
        std::packaged_task<int()>    // wrap calcValue so it
            pt(calcValue);            // can run asynchronously
        
        auto fut = pt.get_future(); // get future for pt

        std::thread t(std::move(pt)); // run pt on t

        // 3 possability:
        // 1) Nothing
        // 2) Join
        // 3) Detach
    }
    return 0;
}