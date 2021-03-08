#include <mutex>
#include <iostream>

void f(int a) {
    std::cout << "f(int)" << std::endl;
}

void f(bool a) {
    std::cout << "f(bool)" << std::endl;
}

void f(void*) {
    std::cout << "f(void*)" << std::endl;
}

struct Point { };

template<typename FuncType,
         typename MuxType,
         typename PtrType>
decltype(auto) lockAndCall(
    FuncType func, // C++14
    MuxType& mutex,
    PtrType ptr)
{
    std::lock_guard<std::mutex> g(mutex);
    return func(ptr);
}

int f1(int a){ 
    std::cout << "int" << std::endl;
    return 0;
} // call these only when
double f2(const std::string& b){
    std::cout << "std::string" << std::endl;
    return 0.0;
} // the appropriate
bool f3(const Point* pw) {
    std::cout << "Point ptr" << std::endl;
    return false;
} // mutex is locked

int main() {
    f(0); // calls f(int), not f(void*)
    // f(NULL); main.cpp:18:5: error: call to 'f' is ambiguous

    f(nullptr);


    std::mutex f1m, f2m, f3m;
    // auto result1 = lockAndCall(f1, f1m, 0); // error!
    // auto result2 = lockAndCall(f2, f2m, NULL); // error!
    auto result3 = lockAndCall(f3, f3m, nullptr); // fine
}