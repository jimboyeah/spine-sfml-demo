#include <iostream>
#include <string>

using namespace std;

// Declarations
class House;
class Jack;
class Grace
{
public:
    void tryAccess(House h);
};


// Implementations
class House 
{
    friend class Jack;
    friend void Funky(House);
    friend void Grace::tryAccess(House);
public:
    string outdoor = "outside of the House.";
protected: 
    // accessible for friend
    string indoor = "inside of the House.";
private:
    // accessible for friend
    string bedroom = "inside of the Bedroom!";
};

class Jack
{
public:
    Jack(House h)
    {
        cout << "Jack is " << h.outdoor << "\n";
        cout << "Jack is " << h.indoor << "\n";
        cout << "Jack is " << h.bedroom << "\n";
    }
};

class Son: public Jack 
{
    Son(House h): Jack(h)
    {
        cout << "Jack's son is " << h.outdoor << "\n";
        // unaccessable
        // cout << "Jack's son is " << h.indoor << "\n";
        // cout << "Jack's son is " << h.bedroom << "\n";
    }
};

void Grace::tryAccess(House h)
{
    cout << "Grace is " << h.outdoor << "\n";
    cout << "Grace is " << h.indoor << "\n";
    cout << "Grace is " << h.bedroom << "\n";
}

void Funky(House h)
{
    cout << "Funky is " << h.outdoor << "\n";
    cout << "Funky is " << h.indoor << "\n";
    cout << "Funky is " << h.bedroom << "\n";
}

int main(void)
{
    House h;
    Jack j(h);
    Grace g;
    g.tryAccess(h);
    Funky(h);
    return EXIT_SUCCESS;
}
