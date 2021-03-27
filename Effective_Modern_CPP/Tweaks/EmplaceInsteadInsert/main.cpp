#include <iostream>
#include <vector>
#include <memory>
#include <regex>
#include <list>

class Widget {}; 

void killWidget(Widget* pWidget) {
    std::cout << "Killing widget" << std::endl;
}

int main() {
    std::vector<std::string> vs; // container of std::string
    vs.push_back("xyzzy");       // add string literal

    // What compiler actually does
    // vs.push_back(std::string("xyzzy")); // create temp. std::string
                                           // and pass it to push_back

    vs.emplace_back("xyzzy"); // construct std::string inside
                              // vs directly from "xyzzy"


    std::string queenOfDisco("Donna Summer");
    vs.push_back(queenOfDisco); // copy-construct queenOfDisco
                                // at end of vs
    vs.emplace_back(queenOfDisco); // ditto

    vs.emplace(vs.begin(), "xyzzy"); // add "xyzzy" to
                                     // beginning of vs



    std::list<std::shared_ptr<Widget>> ptrs;

    // Construct temporary shared ptr before insert
    ptrs.push_back(std::shared_ptr<Widget>(new Widget, killWidget));
    ptrs.push_back({ new Widget, killWidget });

    // First create Widget and then construct shared ptr inside emplace.
    // If case of exception this lead to memory leak
    ptrs.emplace_back(new Widget, killWidget);

    std::shared_ptr<Widget> spw(new Widget, // create Widget and
        killWidget); // have spw manage it
    ptrs.push_back(std::move(spw)); // add spw as rvalue

    std::shared_ptr<Widget> spw2(new Widget, killWidget);
    ptrs.emplace_back(std::move(spw2));




    // Explicit convertation issue
    std::vector<std::regex> regexes;
    // regexes.emplace_back(nullptr); // add nullptr to container
                                    // of regexes?
                                    // Segfault, cant assign nullptr to regex

    // std::regex r1 = nullptr; // error! won't compile
    std::regex r2(nullptr); // compiles
    return 0;
}