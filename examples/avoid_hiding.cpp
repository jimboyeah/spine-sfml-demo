class Base {
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int) {};
    void mf3() {};
    void mf3(double d) {};
};
class Derived: public Base {
public:
    // using Base::mf1;       // make all things in Base named mf1 and mf3
    // using Base::mf3;       // visible (and public) in Derived's scope
    virtual void mf1() {};
    void mf3() {};
};

int main()
{
    Derived d;
    // d.mf1(1);       // Error Derived::mf1() hide Base::mf1()
    // d.mf3(1);       // Error Derived::mf3() hide Base::mf3()
    d.Base::mf1(2); // OK always
    d.Base::mf3(2); // OK always
}
