#include <iostream>
#include <vector>
using namespace std;

class HumanBeing 
{
public:
    // HumanBeing() {}
    HumanBeing(int = 0) {}
    // pure virtual make it to be an abstract class
    virtual const char* vf() const {return "HB";} /*= 0*/;
    virtual ~HumanBeing() {}
};
class VMan1 : virtual public HumanBeing 
{
public:
    VMan1() : HumanBeing(1) {}
    const char* vf() const { return "VMan1"; }
};
class VMan2 : virtual public HumanBeing 
{
public:
    VMan2() : HumanBeing(2) {}
    const char* vf() const { return "VMan2"; }
};
class MI : public VMan1, public VMan2 
{
public:
    MI() : HumanBeing(3) {}
    const char* vf() const {
        return VMan1::vf(); // MUST disambiguate
    }
};
class XMan : public MI 
{
public:
    // You must ALWAYS init the virtual base:
    XMan()  :HumanBeing(4) {}
};

string im = "I'm file static";

int main() {
    HumanBeing hb;
    XMan man;
    vector<HumanBeing*> b;
    VMan1 *vman1 = new VMan1;
    b.push_back(vman1);
    VMan2 *vman2 = new VMan2;
    b.push_back(vman2);
    MI *mi = new MI;
    b.push_back(mi);
    XMan *xman = new XMan;
    b.push_back(xman);
    for(int i = 0; i < b.size(); i++)
        cout << b[i]->vf() << endl;
}

/*
Thinking in C++ 2nd edition
Volume 2: Standard Libraries &
Advanced Topics

The most-derived class is the one you’re currently in, and is particularly important when
you’re thinking about constructors. In the previous example, HumanBeing is the most-derived class
inside the HumanBeing constructor. Inside the VMan1 constructor, VMan1 is the most-derived class, and
inside the MI constructor, MI is the most-derived class.

When you are using a virtual base class, the most-derived constructor is responsible for
initializing that virtual base class. That means any class, no matter how far away it is from the
virtual base, is responsible for initializing it. 
*/

