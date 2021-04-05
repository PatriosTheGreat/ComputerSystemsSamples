#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Widget {
public:
    Widget(int order) : order_(order) {}

    int get_order() const {
        return order_;
    }

private:
    int order_;
};

bool qualityCompare(const Widget& lhs, const Widget& rhs)
{
    return lhs.get_order() > rhs.get_order(); 
    // return whether lhs's quality is greater than rhs's quality
}

bool hasAcceptableQuality(const Widget& w)
{
    return w.get_order() < 1;
    // return whether w has a quality rating of 5 or better;
}
int main() {
    {
        vector<Widget> widgets;
        widgets.reserve(10);
        for (int i = 0; i < 10; i++) {
            widgets.push_back(Widget(i));
        }

        partial_sort(widgets.begin(), // put the best 5 elements
            widgets.begin() + 5,      // (in order) at the front of
            widgets.end(),            // widgets
            qualityCompare);

        for (const Widget& widget : widgets) {
            cout << widget.get_order() << " "; 
        }

        cout << endl; 
    }

    {
        vector<Widget> widgets;
        widgets.reserve(10);
        for (int i = 9; i >= 0; i--) {
            widgets.push_back(Widget(i));
        }

        nth_element(widgets.begin(),     // put the best 5 elements
                    widgets.begin() + 5, // at the front of widgets,
                    widgets.end(),       // but don't worry about
                    qualityCompare);     // their order

        for (const Widget& widget : widgets) {
            cout << widget.get_order() << " "; 
        }

        cout << endl; 
    }

    {
        vector<Widget> widgets;
        widgets.reserve(10);
        for (int i = 0; i < 10; i++) {
            widgets.push_back(Widget(i));
        }

        vector<Widget>::iterator goodEnd =            // move all widgets satisfying
                    partition(widgets.begin(),        // hasAcceptableQuality to
                              widgets.end(),          // the front of widgets, and
                              hasAcceptableQuality);  // return an iterator to the first
                                                      // widget that isn't satisfactory

        for (const Widget& widget : widgets) {
            cout << widget.get_order() << " "; 
        }

        cout << endl; 
    }
}