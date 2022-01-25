
## ⚡ C++ FAQs Virtual Functions

C++ FAQs Virtual Functions

- FAQ 8.05 Should an overridden virtual function throw an exception?
- FAQ 8.06 Can an overridden virtual function be a no-op?
- FAQ 8.07 Why does C++ make it so hard to fix the Ostrich/Bird dilemma?
- FAQ 20.13 When the constructor of a base class calls a virtual function, why isn't the override called?
- FAQ 20.14 When a base class destructor calls a virtual function, why isn't the override called?
- FAQ 21.02 What is a virtual member function?
- FAQ 21.03 How much does it cost to call a virtual function compared to calling a normal function?
- FAQ 21.04 How does C++ perform static typing while supporting dynamic binding?
- FAQ 21.05 Can destructors be virtual?
- FAQ 21.06 What is the purpose of a virtual destructor?
- FAQ 21.07 What is a virtual constructor?
- FAQ 21.08 What syntax should be used when a constructor or destructor calls a virtual function in its object?
- FAQ 21.09 Should the scope operator :: be used when invoking virtual member functions?
- FAQ 21.10 What is a pure virtual member function?
- FAQ 21.11 Can a pure virtual function be defined in the same class that declares it?
- FAQ 21.12 How should a virtual destructor be defined when it has no code?
- FAQ 21.13 Can an ABC have a pure virtual destructor?
- FAQ 21.14 How can the compiler be kept from generating duplicate outlined copies of inline virtual functions?
- FAQ 21.15 Should a class with virtual functions have at least one non-inline virtual function?
- FAQ 24.10 Can an ABC's assignment operator be virtual?
- FAQ 24.11 What should a derived class do if a base class's assignment operator is virtual?
- FAQ 29.05 Can virtual functions be overloaded?
- FAQ 33.12 When should a nonfinal virtual function be invoked with a fully qualified name?


### ✒ FAQ 8.05 virtual 虚函数重写版该抛异常还是 no-op 什么也不做？

C++ FAQs 提出一个问题，该不该在虚函数重写版本中抛出异常，还是 no-op 什么也不做：

- FAQ 8.05 Should an overridden virtual function throw an exception?
- FAQ 8.06 Can an overridden virtual function be a no-op?
- FAQ 8.07 Why does C++ make it so hard to fix the Ostrich/Bird dilemma?

用鸵鸟困局演示 Ostrich / Bird dilemma，假设 Bird::fly() 这个基类方法不抛出异常：

```cpp
#include <iostream>

using namespace std;

class Bird {
public:
    Bird() throw();
    virtual ~Bird() throw();
    int altitude() const throw();
    virtual void fly() throw();
        // PROMISE: altitude() will return a number > 0; never
        // throws an exception
protected:
    int altitude_;
};

Bird::Bird() throw()
: altitude_(0)
{ }

Bird::~Bird() throw()
{ }

int Bird::altitude() const throw()
{ 
    return altitude_; 
}

void Bird::fly() throw()
{ 
    altitude_ = 100; 
}
```

基于基类的约定，fly() 成员函数不会抛出异常。

```cpp
class CannotFly { };
class Ostrich : public Bird {
public:
    virtual void fly() throw(CannotFly);
    // PROMISE: Throws an exception despite what Bird says
};

void Ostrich::fly() throw(CannotFly)
{ 
    throw CannotFly();
    // or Does nothing despite what Bird said (bad!)
}

void sample(Bird& bird) throw()
{
    bird.fly();
}

int main()
{
    Ostrich bird;
    sample(bird);
}
```

对 Bird::fly() 来说，sample() 调用是合理的。

但是对于 Ostrich::fly()，它定义为抛出异常，假如有人合法地将 Ostrich 传递给 sample()，程序就崩了。

不能责怪在 main() 将鸵鸟传递给 sample() 函数，因为鸵鸟遗传自鸟类，因此鸵鸟被认为是鸟类的替代品。

也不能责怪 sample() 相信 Bird::fly() 的承诺。事实上，程序员是应该依赖于规范而不是实现。因此，责任在于编写 Ostrich 鸵鸟类的作者，他声称鸵鸟是鸟类的替代品，尽管鸵鸟的行为不像鸟。

如果 Ostrich::fly() 什么也不做是不是可以呢？虽然这不会导致程序崩溃，但是这种做法也不符合基类约定，执行一个动作就应该有相应的。

教训是，如果基类禁止抛出异常，则不能通过抛出异常或什么也不做来修复不正确的继承。因为不正当继承的根源是违反约定的行为，而抛出异常是函数行为的一部分。

鸵鸟是否可以替代鸟的问题不是 C++ 语言的失败，也不是面向对象技术的失败。这是领域分析的失败，领域分析错误地得出了关于问题领域的结论：所有鸟类飞行时的海拔高度都是正的。稳定的 OO 软件依赖于对问题域的准确理解和在类关系中正确编码问题域知识。如果设计团队中没有人理解问题域，那么设计会有缺陷也就不足为奇了。这突出了“领域专家”在 OO 项目中的关键作用。

### ✒ FAQ 19.10 为什么友元不能是 virtual？

C++ FAQs 常见问题：为什么友元不能是 virtual？

FAQ 19.10 What does it mean that friends aren't virtual?

友元不是动态绑定的，但是有一个简单的 inline 习惯用法使用友元函数的语法启用虚拟函数的功能，即为友元启用动态绑定，这个习语被称为虚拟友元函数。

虚拟友元函数习惯用法是：为友元函数提供动态绑定操作的作用，使用友元函数语法，但操作必须动态绑定时使用它。

友元函数不会动态绑定。但是，有一个简单的单行习惯用法，它使用友元函数的语法启用虚拟函数的功能（即动态绑定）。这个习语被称为虚拟朋友函数习语。

简单地说，就是使用一个 friend 函数去调用一个 protected: virtual member 函数。例如，假设 Shape 类是一个抽象基类，并且通过 cout<< shape 这样的表达来打印信息。其中 shape 是派生自 Shape 的子类对象，例如 Circle。要使用虚拟友元函数习惯用法，operator<< 操作符将要声明为 Shape 的友元，并将可以调用 protected: pure virtual member，如 print(ostream&）const 保护成员函数。

注意，在整个继承层次结构中，只有基类声明了友元 operator<< 操作符，子类没有，但是 operator<< 可以访问子类的虚所保护成员或私有成员。

```cpp
#include <iostream>

using namespace std;

class Shape {
public:
  virtual ~Shape() throw();
  friend ostream& operator<< (ostream& ostr, const Shape& s) throw();
protected:
  virtual void print(ostream& ostr) const throw() = 0;
  // virtual void print(ostream& ostr) const throw();
};

inline ostream& operator<< (ostream& ostr, const Shape& s) throw()
{
  s.print(ostr);
  return ostr;
}
// void Shape::print(ostream& ost) const throw() { 
//  cout << "implementation can be omit for pure virtual function." << endl;
// }
Shape::~Shape() throw() { }

class Circle : public Shape {
public:
  Circle() throw();
protected:
  // virtual void print(ostream& ostr) const throw();
  void print(ostream& ostr) const throw();
  float radius_;
};

Circle::Circle() throw() : radius_(42) { }
void Circle::print(ostream& ostr) const throw()
{ ostr << "Circle of radius " << radius_; }

void userCode(Shape &shape)
{
    cout << shape << endl;
}

int main()
{
    Circle circle;
    userCode(circle);
}
```

例子还有一个可能被忽略的问题，可能会导致报错： error C2804: operator << 二元运算符的参数太多。

重载运算符相当于给类定义成员函数，对于二元运算符它的第一个参数就应该是当前的类，因为成员函数需要类实例去调用，第一个参数就必需是当前的类型，如果有的话，它的作用就是当作 this 指针指向当前实例。

但是这个例子中，Shape 又必需放到第二个参数中，第一个参数必需是 ostream，否则 operator << 无法按需要定义。

解决方法也就是使用友元函数，将这个要重载的二元运算符声明为友元函数，这样它就不需要使用类实例去调用成员。


### ✒ FAQ 20.12 没有代码的 virtual 解构器如何定义?

- FAQ 21.12 How should a virtual destructor be defined when it has no code?
- FAQ 20.05 What happens when a destructor is executed?

应该使用 inline virtual functions 作为解构函数，避免子类解构时自动调用父类解构函数，以下示范代码定义了 `inline Base::~Base()`，编译器会自动为子类合成这个解构函数，而不是在 `Derived::~Derived()` 额外调用一次。

```cpp
#include <iostream>
using namespace std;

// Declarationss
class Base {
public:
  virtual void f() throw();
  virtual void g() throw();
  virtual ~Base()  throw();
};

class Derived : public Base {
public:
  virtual void f() throw();
};

// Definitions ("implementation" is for interface)
void Base::f() throw() { cout << "Base::f()\n"; }
void Base::g() throw() { cout << "Base::g()\n"; }
inline Base::~Base()  throw() { cout << "Not really a ~Base::Base()\n"; }

void Derived::f() throw() { cout << "Derived::f()\n";  }

int main()
{
  Base b; //                <-- OK: destructor really is a Base:~Base()
  b.f();
  b.g();
  Derived d; //             <-- OK: destructor really is a Derived:~Derived()
  d.f();
  d.g();
}
```


### ✒ FAQ 20.13 基类构造器调用 virtual 函数时为何不是调用重写版本?

C++ FAQs 常见问题：当基类的构造函数或解构函数调用虚函数时，为什么不调用重写方法？

- FAQ 20.13 When the constructor of a base class calls a virtual function, why isn't the override called?
- FAQ 20.14 When a base class destructor calls a virtual function, why isn't the override called?

这个问题很明显，构造函数就是保证使用类实例之前构造内存中的数据结构的。在构造器中调用的虚函数只可以是本身实现的，而不是子类重写的，因为它们还没有完成构造。解构过程和构造过程完全相反，在基类解构前，先要确定子类完全解构。

```cpp
#include <iostream>
using namespace std;

class MemberObject {
public:
    MemberObject()     throw();
    void doSomething() throw();
};

MemberObject::MemberObject()     throw()
{ cout << "MemberObject ctor\n"; }
void MemberObject::doSomething() throw()
{ cout << "MemberObject used\n"; }

class Base {
public:
    Base()           throw();
    virtual void f() throw();
};

Base::Base()   throw() { cout << "Base ctor\n"; f(); }
void Base::f() throw() { cout << "Base::f()\n"; }

class Derived : public Base {
public:
    Derived()        throw();
    virtual void f() throw();
protected:
    MemberObject m_;
};

Derived::Derived() throw()
: Base(), m_() { cout << "Derived ctor\n"; }
void Derived::f()  throw()
{ cout << "Derived::f()\n"; m_.doSomething(); }

int main()
{
    Derived d;
    cout << "====\n";
    d.f();
}
// Output:
// Base ctor
// Base::f()
// MemberObject ctor
// Derived ctor
// ====
// Derived::f()
// MemberObject used
```

### ✒ FAQ 21.07 virtual 虚构造器是什么？

C++ FAQs 常见问题：虚构造器是什么？

- FAQ 21.07 What is a virtual constructor?
- FAQ 16.05 What is an analogy for static member functions?

尽管构造函数是不能为虚拟的，但变通的方法是，不要认为构造函数是对象上的普通成员函数，想象它们是创建对象的静态成员函数。有一种习惯用法 virtual constructor idiom，可以实现对象的创建而不需要指定具体类型。

比如，以下示范代码中，给 Shape 类中定义了：

- virtual clone() const 方法，作为拷贝构造器使用。
- virtual createSimilar() const 方法，作为默认构造器使用。

注意，后面的 const 修饰符可以供编译器作为重载参考。

以下示范代码中，子类实现了父类的虚函数，virtual 关键字可以省略，但为了直观还是使用了。这些虚函数当作构造器使用，通过基类指针调用 clone() 这些方法就可以实现子类实例的创建，这就是虚拟多态机制的好处。

FAQ 21.08 在构造器、解构器中调用虚拟函数可以使用作用域操作符，Scope operator :: 来指定要调用哪个类作用域下的虚函数，如 Shape::draw()。

FAQ 21.09 在子类中也可以使用 Scope operator :: 来调用虚函数，它的目的是跳过虚拟多态机制，因为动态绑定是
对于用户来说非常重要，用户代码通常应该避免使用它。

注意，虚函数返回的是经过 auto_ptr 智能指针包装的对象，在 C++11 后，这个智能指针已经被 unique_ptr 取代。使用智能指针的好处是可以自动进行内存管理，注意代码中的注解。

```cpp
#include <new>
#include <memory>
#include <iostream>
using namespace std;

class Shape;

typedef auto_ptr<Shape>  ShapePtr;
// typedef unique_ptr<Shape>  UniShapePtr;

class Shape {
public:
           Shape()                       throw();
  virtual ~Shape()                       throw();
  virtual void draw() const              throw() = 0;
  virtual ShapePtr clone() const         throw(bad_alloc) = 0;
  virtual ShapePtr createSimilar() const throw(bad_alloc) = 0;
};

Shape::Shape()  throw() { }
Shape::~Shape() throw() { }

class Circle : public Shape {
public:
  Circle(int radius=0)                   throw();
  virtual void draw() const              throw();
  virtual ShapePtr clone() const         throw(bad_alloc);
  virtual ShapePtr createSimilar() const throw(bad_alloc);
protected:
  int radius_;
};

Circle::Circle(int radius) throw() : Shape(), radius_(radius) { }
void Circle::draw() const throw()
{ 
  cout << "Circle: radius=" << radius_ << '\n'; 
}
ShapePtr Circle::createSimilar() const throw(bad_alloc)
{ 
  return ShapePtr(new Circle()); 
}
ShapePtr Circle::clone() const throw(bad_alloc)
{ 
  return ShapePtr(new Circle(*this)); 
}

void userCode(ShapePtr s) throw()
{
  cout << "userCode() number 1: ";
  s->draw();
  ShapePtr copy = s->clone();
  cout << "userCode() number 2: ";
  copy->draw();
  ShapePtr similar = s->createSimilar();
  cout << "userCode() number 3: ";
  similar->draw();
} // (1) "copy" and "similar" are automatically deleted here (see FAQ 2.07)

int main()
{
  ShapePtr c(new Circle(42));
  cout << "main() number 1: ";
  c->draw();
  userCode(c);
  // (2) Because of auto_ptr's copy semantics, c will be NULL here (see FAQ 2.11)
}
```
