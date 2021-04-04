#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

class Employee {
public:
    const string& name() const {
        return name_;
    } // get employee name
    void setName(const string& name) {
        name_ = name;
    } // set employee name
    const string& title() const {
        return title_;
    } // get employee title
    void setTitle(const string& title) {
        title_ = title;
    } // set employee title
    int idNumber() const {
        return 42;
    } // get employee ID number

private:
    string name_;
    string title_;
};


struct IDNumberLess :
                    public binary_function<Employee, Employee, bool> { // see Item 40
    bool operator()( const Employee& lhs,
                    const Employee& rhs) const
    {
        return lhs.idNumber() < rhs.idNumber();
    }
};

int main() {
    map<int, string> m;
    // m.begin()->first = 10;   // error! map keys can't be changed
    multimap<int, string> mm;
    // mm.begin()->first = 20;  // error! multimap keys can't
                                //be changed, either

    typedef set<Employee, IDNumberLess> EmplDSet;
    EmplDSet se;                // se is a set of employees
                                // sorted by ID number
    Employee selectedID; // variable to hold employee
                        // with selected ID number
    se.insert(selectedID);
    {
        EmplDSet::iterator i = se.find(selectedID);
        if (i != se.end()){
            // DONT DO LIKE THIS, this wont modify value in set
            const_cast<Employee&>(*i).setTitle("Corporate Deity"); // give employee new title
            cout << "name set" << endl; 
        }

        
        EmplDSet::iterator i2 = se.find(selectedID);
        cout << i2->title() << endl;
    }

    EmplDSet::iterator i =
        se.find(selectedID); // Step 1: find element to change
    if(i!=se.end()){
        Employee e(*i); // Step 2: copy the element
        se.erase(i++); // Step 3: remove the element;
        // increment the iterator to maintain
        // its validity (see Item 9)
        e.setTitle("Corporate Deity"); // Step 4: modify the copy
        se.insert(i, e); // Step 5: insert new value; hint that its
        // location is the same as that of the
        //original element
    }
}