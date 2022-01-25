#include <iostream>
#include <string>

using namespace std;

// Declarations
class House;
class Grace
{
public:
    Grace(House);
    string name = "Grace";
};


// Implementations
class House 
{

};

Grace::Grace(House h)
{
    cout << "Grace(House)" << endl;
}

class Curious
{
public:
    void autoConstruct(Grace baby)
    {
        cout << "baby name: " << baby.name << "\n";
    }
};

int main(void)
{
    House h;
    Grace g(h);
    Curious test;
    test.autoConstruct(h);

    return EXIT_SUCCESS;
}
