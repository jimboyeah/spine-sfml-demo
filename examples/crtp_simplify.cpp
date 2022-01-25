#include <iostream>

template <typename T>
struct NumericalFunctions
{
    void scale(double multiplicator)
    {
        T& underlying = static_cast<T&>(*this);
        underlying.setValue(underlying.getValue() * multiplicator);
    }
    void square()
    {
        T& underlying = static_cast<T&>(*this);
        underlying.setValue(underlying.getValue() * underlying.getValue());
    }
    void setToOpposite()
    {
        scale(-1);
    };
};

class Sensitivity : public NumericalFunctions<Sensitivity>
{
    double value_;
public:
    double getValue() const { return value_; };
    void setValue(double value) { value_ = value; };
    // rest of the sensitivity's rich interface...
};

class Sens: public Sensitivity {};


template <typename T>
class Amount
{
public:
    double getValue() const
    {
        return static_cast<T const&>(*this).getValue();
    }
};

class Constant42 : public Amount<Constant42>
{
public:
    double getValue() const {return 42;}
};

class Variable : public Amount<Variable>
{
public:
    explicit Variable(int value) : value_(value) {}
    double getValue() const {return value_;}
private:
    int value_;
};

template<typename T>
void print(Amount<T> const& amount)
{
    std::cout << amount.getValue() << '\n';
}

int main()
{
    Constant42 c42;
    print(c42);
    Variable st(2l);
    print(st);
    Sens ss;
    ss.setValue(9);
    std::cout << ss.getValue();
}