#include <iostream>

struct V 
{
    V(int i){}; // no default constructor
};
struct A 
{
    A() {}; // default constructor
};
struct B : virtual V, virtual A 
{
    B() : V{1} { /* ... */ }; // default constructor ; must initialize base V
};
class C : virtual V 
{
public:
    C(int i) : V{i} { /* ... */ }; // must initialize base V
};
class D : virtual public B, virtual public C {
// implicitly gets the virtual base V from B and C
// implicitly gets virtual base A from B
public:
    // D() { /* ... */ } // error : no default constructor for C or V
    // D(int i) :C{i} { /* ... */ }; // error : no default constructor for V
    D(int i, int j) :V{i}, C{j} { /* ... */ } // OK
};
// The C++ Programming Language, Forth Edition

int main()
{
    D d(1,2);
}