#include <iostream>

// static polymorphism demo
template <class impl>
class base : public impl { 
public: void op() { impl::op(); }};

struct impl { void op() {  std::cout<< "work here\n"; }};


// F-bound polymorphism
template <typename Child>
struct Base
{
    void doAction()
    {
        static_cast<Child*>(this)->implementation();
    }
private:
    Base(){};
    friend Child;
};

template<typename T>
void Action(Base<T> &thing)
{
    thing.doAction();
}

struct Derived : Base<Derived>
{
    void implementation()
    {
        std::cerr << "F-bound polymorphism\n";
    }
};

int main()
{
    base<impl>().op();
    Derived d;
    d.doAction();
    Action(d);
}
