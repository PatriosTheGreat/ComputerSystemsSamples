#include <iostream>
#include <memory>
#include <vector>

struct Widget {

};

int computePriority() {
    throw new std::exception();
}

void processWidget(std::shared_ptr<Widget> w, int prior) { // potential
    std::cout << "processWidget" << std::endl;
}

class ReallyBigType { };

int main() {
    
    {
        auto upw1(std::make_unique<Widget>()); // with make func
        std::unique_ptr<Widget> upw2(new Widget); // without make func
        auto spw1(std::make_shared<Widget>()); // with make func
        std::shared_ptr<Widget> spw2(new Widget); // without make func
    }

    try {
        // Compiler can generate followed code:
        // 1. Perform “new Widget”. -- leak
        // 2. Execute computePriority. -- throws exception
        // 3. Run std::shared_ptr constructor.
        
        processWidget(std::shared_ptr<Widget>(new Widget), // potential
                    computePriority());

        
    }
    catch (...) {
        std::cout << "exception" << std::endl;
    }

    {
        // Two allocations
        std::shared_ptr<Widget> spw(new Widget);
    }

    {
        // Single allocation
        auto spw = std::make_shared<Widget>();
    }

    {
        auto widgetDeleter = [](Widget* pw) { std::cout << "Removing" << std::endl; };

        // No way without make unique
        std::unique_ptr<Widget, decltype(widgetDeleter)>
            upw(new Widget, widgetDeleter);

        std::shared_ptr<Widget> spw(new Widget, widgetDeleter);
    }

    {
        //  Both calls constructor and make 10 copies of 20
        auto upv = std::make_unique<std::vector<int>>(10, 20);
        auto spv = std::make_shared<std::vector<int>>(10, 20);

        std::cout << "Upv size: " << upv->size() << " spv size: " << spv->size() << std::endl;
    }

    {
        // create std::initializer_list
        auto initList = { 10, 20 };
        // create std::vector using std::initializer_list ctor
        auto spv = std::make_shared<std::vector<int>>(initList);

        std::cout << "Spv size: " << spv->size() << std::endl;
    }

    {
        auto pBigObj = // create very large
        std::make_shared<ReallyBigType>(); // object via
        // std::make_shared

          // create std::shared_ptrs and std::weak_ptrs to
          // large object, use them to work with it
          
          // final std::shared_ptr to object destroyed here,
          // but std::weak_ptrs to it remain
          
          // during this period, memory formerly occupied
          // by large object remains allocated
          
          // final std::weak_ptr to object destroyed here;
          // memory for control block and object is released
    }

    {
        std::shared_ptr<ReallyBigType> pBigObj(new ReallyBigType);
        // create very large
        // object via new
        
        // as before, create std::shared_ptrs and
        // std::weak_ptrs to object, use them with it
        
        // final std::shared_ptr to object destroyed here,
        // but std::weak_ptrs to it remain;
        // memory for object is deallocated
        
        // during this period, only memory for the
        // control block remains allocated
        
        // final std::weak_ptr to object destroyed here;
        // memory for control block is released
    }

    // Right way to create manually object for shared_ptr if we need it
    {
        auto cusDel = [](Widget* pw) { std::cout << "Removing" << std::endl; };
        std::shared_ptr<Widget> spw(new Widget, cusDel);
        processWidget(std::move(spw), computePriority()); // correct, but not
        // optimal; see below
    }


}