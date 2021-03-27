#include <iostream>
#include <thread>
#include <future>

int doAsyncWork() {
    std::cout << "Do work async" << std::endl;

    return 1;
}

int main() {
    // Thread-based
    std::thread t(doAsyncWork);
    t.join();

    // Task-based
    auto fut = std::async(doAsyncWork);
    fut.wait();
    return 0;
}