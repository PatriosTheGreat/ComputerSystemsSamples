#include <iostream>
#include <vector>

class Widget {
public:
    // bad, need to wright two functions
    /*
    void addName(const std::string& newName) // take lvalue;
    { names.push_back(newName); }            // copy it
    
    void addName(std::string&& newName)      // take rvalue;
    { names.push_back(std::move(newName)); } // move it; see
    // Item 25 for use of std::move
    */

    // bad, universal reference
    /*
    template<typename T> // take lvalues
    void addName(T&& newName) // and rvalues;
    { // copy lvalues,
        names.push_back(std::forward<T>(newName)); // move rvalues;
    } // see Item 25
    // for use of
    // std::forward
    */

    // Pass-by-value, bad for C++98, but ok for C++11
    void addName(std::string newName) // take lvalue or
    { names.push_back(std::move(newName)); } // rvalue; move it
private:
    std::vector<std::string> names;
};

class Password {
public:
    explicit Password(std::string pwd) // pass by value
        : text(std::move(pwd)) {} // construct text

    void changeTo(std::string newPwd) // pass by value
    { text = std::move(newPwd); } // assign text

    void changeTo(const std::string& newPwd) // the overload
    {                                        // for lvalues
        text = newPwd; // can reuse text's memory if
                       // text.capacity() >= newPwd.size()
    }
private:
    std::string text; // text of password
};

int main() {
    Widget w;
    std::string name("Bart");
    w.addName(name); // call addName with lvalue

    w.addName(name + "Jenne"); // call addName with rvalue
                               // (see below)



    std::string initPwd("Supercalifragilisticexpialidocious");
    Password p(initPwd);

    std::string newPassword = "Beware the Jabberwock";
    p.changeTo(newPassword);
    return 0;
}