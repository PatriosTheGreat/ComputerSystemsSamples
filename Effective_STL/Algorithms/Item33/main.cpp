#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Widget{
public:

    bool isCertified() const {
        return false;
    } // whether the Widget is certified

};

void delAndNullifyUncertified(Widget*& pWidget) // if *pWidget is an
{ // uncertified Widget,
    cout << pWidget << endl;
    if (pWidget && !pWidget->isCertified()) { // delete the pointer
        delete pWidget; //and set it to null
        pWidget = nullptr;
    }
}

int main() {
    {
        vector<Widget*> v;
        v.push_back(new Widget);

        // Mangeled pointer if any other object in v points to the same object
        v.erase(remove_if(
                    v.begin(), v.end(), // erase ptrs to
                    not1(mem_fun(&Widget::isCertified))),
                    v.end()); //Widgets; see
    }
    
    vector<Widget*> v;
    auto w = new Widget;
    v.push_back(w);
    v.push_back(w);

    for_each(v.begin(), v.end(),    // sdelete and set to
        delAndNullifyUncertified);  // null all ptrs to
                                    // uncertified widgets

    v.erase( remove(v.begin(), v.end(), // eliminate null ptrs
            static_cast<Widget*>(0)), // from v; 0 must be
            v.end()); //cast to a ptr so C++ correctly deduces the type of remove's 3rd param

    cout << v.size() << endl;
}