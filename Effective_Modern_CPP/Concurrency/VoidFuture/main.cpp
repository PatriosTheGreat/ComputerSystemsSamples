#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <condition_variable>

std::promise<void> p;
void react() { // func for reacting task
    std::cout << "Reacting" << std::endl;
}

std::promise<void> p; // as before
void detectGood() // now for multiple
{                 // reacting tasks
    auto sf = p.get_future().share(); // sf's type is
                                      // std::shared_future<void>
    std::vector<std::thread> vt; // container for
    // reacting threads
    for (int i = 0; i < 1 /* threadsToRun */; ++i) {
        vt.emplace_back([sf]{ sf.wait(); // wait on local
        react(); }); // copy of sf; see
    } // Item 42 for info
    // on emplace_back
    // detect hangs if
    // this "…" code throws!
    p.set_value(); // unsuspend all threads
    
    for (auto& t : vt) { // make all threads
        t.join(); // unjoinable; see Item 2
    } // for info on "auto&"
}

void detectWrong() // func for detecting task
{
    std::thread t([] // create thread
                {
                    p.get_future().wait(); // suspend t until
                    react(); // future is set
                });
    // here, t is suspended
    // prior to call to react
    p.set_value(); // unsuspend t (and thus
    // call react)
     // do additional work
    t.join(); // make t unjoinable
} // (see Item 37)

int main() {
    std::condition_variable cv; // condvar for event
    std::mutex m;               // mutex for use with cv

    cv.notify_one(); // tell reacting task

    // prepare to react
    {   // open critical section
        std::unique_lock<std::mutex> lk(m); // lock mutex
        // cv.wait(lk); // wait for notify;
        // this isn't correct!
        // react to event
        // (m is locked)
    }   // close crit. section;
    // unlock m via lk's dtor
    // continue reacting
    // (m now unlocked)


    {
        std::atomic<bool> flag(false); // shared flag; see
        // Item 40 for std::atomic
        // detect event

        flag = true; // tell reacting task

        // prepare to react
        // while (!flag); // wait for event
        // react to event
    }

    /*
    {
        std::condition_variable cv; // as before
        std::mutex m;
        bool flag(false); // not std::atomic

        // detect event
        {
            std::lock_guard<std::mutex> g(m); // lock m via g's ctor
            flag = true;                      // tell reacting task
                                              // (part 1)
        } // unlock m via g's dtor

        cv.notify_one(); // tell reacting task
                         // (part 2)

                         

        // reacting task:

        // prepare to react
        { // as before
            std::unique_lock<std::mutex> lk(m); // as before
            cv.wait(lk, [flag] { return flag; }); // use lambda to avoid
            // spurious wakeups
            // react to event
            // (m is locked)
        }
        // continue reacting
        // (m now unlocked)
    }
    */



   
}