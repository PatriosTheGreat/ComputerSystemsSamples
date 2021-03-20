#include <iostream>
#include <memory>
#include <unordered_map>

struct Pointer {

};

void expire() {
    auto spw = // after spw is constructed,
        std::make_shared<Pointer>(); // the pointed-to Pointer's

    std::weak_ptr<Pointer> wpw(spw);
    spw = nullptr;

    if (wpw.expired()) {
        std::cout << "Expired" << std::endl;
    }

}

void lock() {
    auto spw = // after spw is constructed,
    std::make_shared<Pointer>(); // the pointed-to Pointer's

    std::weak_ptr<Pointer> wpw(spw);

    auto spw2 = wpw.lock(); // spw2 will be null if wpw is expired;
    std::cout << (spw2 == nullptr) << std::endl;
}

std::shared_ptr<const Pointer> fastLoadPoint(int id)
{
    static std::unordered_map<int,
        std::weak_ptr<const Pointer>> cache;
    auto objPtr = cache[id].lock(); // objPtr is std::shared_ptr
    // to cached object (or null
    // if object's not in cache)
    if (!objPtr) { // if not in cache,
        objPtr = std::make_shared<Pointer>(); // load it
        cache[id] = objPtr; // cache it
    }
    return objPtr;
}

int main() {
    expire();
    lock();

}