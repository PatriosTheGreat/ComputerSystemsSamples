#include <iostream>
#include <iostream>
#include <thread>
#include <future>

using namespace std::literals;

int f() {
    std::this_thread::sleep_for(1s);
    return 1;
}

template<typename F, typename... Ts>
inline
std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f, Ts&&... params)          // return future
{                                           // for asynchronous
    return std::async(std::launch::async,   // call to f(params...)
                      std::forward<F>(f),
                      std::forward<Ts>(params)...);
}

int main() {
    auto fut1 = std::async(f); // run f using
                               // default launch
                               // policy
    auto fut2 = std::async(std::launch::async |   // run f either
                           std::launch::deferred, // async or
                           f);                    // deferred


    auto fut = std::async(f); // run f asynchronously
                              // (conceptually)

    if (fut.wait_for(0s) ==             // if task is
        std::future_status::deferred)   // deferred...
    {
        // use wait or get
    } else {
        while (fut.wait_for(100ms) !=      // loop until f has
                std::future_status::ready) // finished running...
        {                                  // which may never happen!
        }
    }

    auto really_async_fut = reallyAsync(f);  // run f asynchronously;
                                             // throw if std::async
                                             // would throw
    return 0;
}