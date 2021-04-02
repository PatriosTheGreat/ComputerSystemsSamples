#include <vector>
#include <algorithm>
#include <iostream>

template<class T>
void getMutexFor(const T& c)
{ }

template<class T>
void releaseMutexFor(const T& c)
{ }

template<class T>
class Lock
{
public:
	Lock(const T& container) : container_(container)
	{
		getMutexFor(container_);
	}

	~Lock()
	{
		releaseMutexFor(container_);
	}

private:
	const Container& container_;
};

int main() {
    std::vector<int> v;
    Lock<std::vector<int>> lock(v);
    std::vector<int>::iterator first5(
        find(v.begin(), v.end(), 5)); // Line 1
    if (first5 !=v.end()){            //Line 2
        *first5 = 0;                  // Line 3
    }
}