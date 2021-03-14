#include <iostream>

int f(int x) throw(); // no exceptions from f: C++98 style
int f(int x) noexcept; // no exceptions from f: C++11 style

// RetType function(params) noexcept; // most optimizable
// RetType function(params) throw(); // less optimizable
// RetType function(params); // less optimizable


template <class T, size_t N>
void swap(T (&a)[N], // see
T (&b)[N]) noexcept(noexcept(swap(*a, *b))); // Swap of array is no except only if swap of each element is no except


int main() {

}