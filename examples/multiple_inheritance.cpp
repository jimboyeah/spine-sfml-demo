#include <iostream>

class A { public: A(){ std::cout << "A() ";} };
class B : public A { public: B(){ std::cout << "B() ";} };
class C : public B { public: C(){ std::cout << "C() ";} };
class X { public: X(){ std::cout << "X() ";} };
class Y { public: Y(){ std::cout << "Y() ";} };
class Z : public X, public Y { public: Z(){ std::cout << "Z() ";} };
class MI : public C, public Z { public: MI(){ std::cout << "MI() ";} };
class MIV : public C, virtual public Z { public: MIV(){ std::cout << "MIV() ";} };

int main()
{
    MI mi;
    std::cout << "\n========virtual inheritence========\n";
    MIV miv;
}
// A() B() C() X() Y() Z() MI() 
// ========virtual inheritence========
// X() Y() Z() A() B() C() MIV() 