#include <iostream>
#include <vector>

using namespace std;

class Contestant { };

int main() {
    vector<Contestant> contestants;


    for (int i = 0; i < 10000; i++) {
        contestants.push_back(Contestant());
    }

    for (int i = 10; i < 10000; i++) {
        contestants.pop_back();
    }

    std::cout << "size: " << contestants.size() << " capacity: " << contestants.capacity() << std::endl;

    vector<Contestant>(contestants).swap(contestants);

    std::cout << "size: " << contestants.size() << " capacity: " << contestants.capacity() << std::endl;
}