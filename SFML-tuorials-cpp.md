
# 🚩 OOP 面向对象编程

面向对象三大特征： 

- 封装：Encapsulation，封装和隐藏

    - ● 缘由：使用者对定义的属性(成员变量)直接操作会导致数据的错误、混乱或安全性问题
    - ● 办法：隐藏不需要对外提供的实现细节，使用者只能通过事先定制好的方法来访问
    - ● 实现：将属性声明为私有的，再提供公共的方法实现对该属性的操作

- 继承：Inheritance

    - ● 多个类中存在相同属性和行为时，将这些内容抽取到一个新类中，多个类无需再定义这些属性和行为，只要继承那个类即可
    - ● 子类会把父类除构造器之外的所有信息给继承下来
    - ● 子父类的概念是相对的（子类也可以作为其他类的父类，父类也可以作为其他类的子类）
    - ● 子类可以有自己特有属性和方法也可以重写父类定义的方法
    - ● 子类是父类的扩展
    - ● 语法： 修饰符  class  类名(子类)  extends  类名(父类){ }
    - ● 作用 ：提高了代码的复用性，让类与类之间产生了关系，提供了多态的前提

- 多态：Polymorphism，指一个事物存在多种形态

    - 表现形式：

        - ● 方法的重载和重写 overload & override
        - ● 对象的多态性：父类的引用指向子类的对象  如：Person p1 = new Woman();

    - 多态的前提：

        - ● 继承关系
        - ● 子类重写了父类的方法

    - 多态在程序运行分为：（编译时“看左边”，运行时“看右边”）

        - ● 编译状态 ：关注是父类。子类特有的属性和方法不能被编译通过
        - ● 运行状态 ：关注的是子类（真正对象的实体，子类的对象，那么执行的方法就是子类重写的方法）

抽象是人类解决问题的一种高度思维能力，抽象在 OOP 随处可见，而抽象类和接口则一集中体现的两个典型。

继承过后，子类变得越来越具体，父类则更一般，更通用。有时将父类设计得非常抽象，以至于它没有具体的实例，这样的类叫做抽象类。

抽象类：（可以定义和普通类完全一样的内容）

- ● 语法：`privilege abstract class name { }`
- ● 不能被实例化，用来被继承。子类必须重写父类的抽象方法，才能被实例化
- ● 有构造器(所以的类都有构造器)
- ● 抽象类中不一定有抽象方法

抽象方法：（只有方法的声明，没有方法的实现。在定义抽象方法时没有方法体和 { }，结尾分号结束）

- ● 语法：`privilege abstract void/type name(arguments);`
- ● 抽象方法所在的类一定是抽象类 
- ● 子类如果继承的是抽象的父类（有抽象方法），那么子类必须重写父类的所有抽象方法或者子类也是一个抽象类
- ● 若子类继承抽象类，并重写所有的抽象方法，则此类是一个“实体类”，即可以实例化

接口：interface 是一种特殊的抽象类，是抽象方法和常量值定义的集合，没有具体的实现。

- ● 接口类语法：`privilege interface name { }`
- ● 常量(成员变量)语法：`public static final type NAME = value;`（其中 public static final 可以省略，为默认）
- ● 抽象方法语法：`public abstract void/type name(arguments)`（其中 public abstract 可以省略，为默认）
- ● 实现接口语法：`privilege class name implements interface_name { }`（实现多个接口，接口名称之间使用“，”分隔）
- ● 实现类可以继承父类也可以实现接口语法：`privilege class Derived extends BaseClass implements interface_name { }`
- ● 对象的引用语法：`interface_name name = new Derived()` 接口与实现类之间也存在多态性


## ⚡ Inheritances 继承

继承是面向对象编程的基本能力之一，通过继承，可以直接复用现有代码。C++ 的基本继承方式有单继承、多继承、虚继承，涉及内存布局的 Polymorphism 多态特性。

几乎不使用 protected 或 private 继承，通常使用 public 继承，继承权限修饰遵循以下几个规则：

- 公有继承 Public 保持基类原有的访问权限；
- 保护继承 Protected 则将基类的公有权限降级为保护；
- 私有继承 Private 则将基类的所有权限降级为私有；

所谓局部类 local class 就是定义在一个函数内部的类，这个类只能在这个函数内部使用，例子：

```cpp
int main()
{
    class c4
    {
    public:
        int a;
        void foo() {a = 4;}
    };
 
    class c4 ff;
    ff.foo();
    cout << ff.a << endl;
    return 0;
}
```

所谓嵌套类，即在类内部定义的类，根据类的访问修饰符决定外部代码是否可以访问：

```cpp
#include <cstdio>
#include <typeinfo>

class Base
{
    class _neasted
    {
        const char *data = "some secret";
    public:
        void test()
        { 
            printf("%s\n", typeid(*this).name()); 
        };
    };

public:
    Base()
    {
        _neasted _n;
        neasted n;
        printf("Construct %s\n", typeid(*this).name());
        // error: 'char Base::_neasted::data []' is private within this context
        // printf("--> Test _neasted: %s\n", _n.data);
        printf("--> Test neasted: %s\n", n.data);
    }

    ~Base()
    {
        printf("Destructure of %s\n", __FUNCTION__);
    }
    
    class neasted
    {
    public:
        const char *data = "some string";
        void test()
        { 
            printf("%s\n", typeid(*this).name()); 
        }
    };
};


int main()
{
    Base();

    // error: 'class Base::_neasted' is private within this context
    // Base::_neasted _n;
    Base::neasted n;
    printf("%s:\n", __FUNCTION__);
    printf("--> Test neasted: %s\n", n.data);

    return 0;
}
```


## ⚡ Friend & Access Control

C++ 使用 public protected private 三级访问控制权，结构体默认 public 访问权，类默认 private 访问权。

```C++
#include <iostream>

using namespace std;

class Base
{
private:
    int nPrivate;
public:
    int nPublic;
protected:
    int nProtected;
};

class Derived: public Base // public 继承
{
    void AccessTest()
    {
        nPublic = 1;    // Ok 可以访问 public 继承的基类 protected 成员
        nProtected = 1; // Ok 可以访问 public 继承的基类 protected 成员
        //nPrivate = 1; // No 不能访问 public 继承的基类 private 成员
        Derived d;
        // d.nProtected = 1; // Ok 可以从外部访问 public 成员
        // d.nProtected = 1; // No 不能从外部访问 protected 成员
        // d.nPrivate = 1;   // No 不能从外部访问 private 成员
    }
};

int main()
{
    Derived s;
    s.AccessTest();
    return 0;
}
```

Table 14.1 Varieties of Inheritance 展示了各种基本继承关系中父类成员在子类中的访问权：

|  Base's Property   | Public Inheritance | Protected Inheritance | Private Inheritance |
|--------------------|--------------------|-----------------------|---------------------|
| Public members     | Public members     | Protected members     | Private members     |
| Protected members  | Protected members  | Protected members     | Private members     |
| Private members    | NO                 | NO                    | NO                  |
| Implicit upcasting | Yes                | Yes (within)          | No                  |

注意，public 继承方式是完全支持隐式转型的，即编译器会直接将子类实例变量或指针赋值给父类实例变量或指针。

友元机制允许一个类向另一个类公开其所有成员访问权的，访问权可以授予指定的函数或者类及类成员方法。

友元的声明只能出现在类声明内，通常，将友元声明成组地放在类定义的开始或结尾是个好主意。声明友元后，就表示信任友元对自身的私密数据或成员进行访问：

```cpp
class MyFiends {
    friend void set_show(int x, A &a);
    friend void B::set_show(int x, A &a);
    friend class C;
    friend int main();
private:
    int something_for_my_friend;
}
```

友元关系不可继承、不可传递、不可交换，构造函数不能作为友元，友友不分 public/proteced/private。但是为了方便文档的构建，通常应该在 public 下声明，因为文档构建时可能忽略保护、私有的成员。

例如，不可传递：

- A 类声明 B 为友元，那么只能保证 B 类可以访问 A 类的所有成员。
- B 类声明 C 为友元，也就只能保证 C 类可以访问 B 类的所有成员。
- C 类不是 A 类的友元，所以不可以访问 A 类的非公有成员。

类、成员、函数友元用法示范：

```cpp
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
```

下面代码中，基类 B 定义了三种访问权限的成员方法，在 B 在中任一个方法中都可以调用 apple、pie、pine 三个成员方法。而 X、Y、Z 分别以三种限继承 B，X、Y、Z 类的继承方法不同，使得它们的子类对基类 B 的成员方法有不同的访问权限，但在 X、Y、Z 内不可访问的方法只有 pine 这个私有方法。N 类继承了 Z 类，由于 Z 类的私有继承使得 N 类对基类 B 的所有成员都不具有访问权限。

在类外部环境中，即 main 函数中只有 B 类及子类 X 可以访问 apple() 方法。C++ 中没有 super 或 parent 等关键字，想要调父类方法，只能以两个冒号指定父类名称及方法名 B::apple() 这种方式调用。

```cpp
#include <iostream>

class B {
    // 公有成员方法允许子类访问
    public: void apple() {
        std::cout << "B::apple() is called" << std::endl; 
    }

    // 保护成员方法不允许私有继承的子类访问
    protected: void pie() {
        std::cout << "B::pie() is called" << std::endl; 
    }

    // 私有成员方法只允许友元子类访问
    private: void pine() {
        std::cout << "B::pine() is called" << std::endl; 
    }

    friend class F; // 友元类声明
};

class X: public    B { 
    /* 公有继承不可访问基类私有方法 pine() */ 
};

class Y: protected B { 
    /* 保护继承，基类公有成员将降级为保护成员，不可访问基类私有方法 pine() */ 
};

class Z: private   B { 
    /* 私有继承将隐藏基类，不暴露给下一级代码 */ 
    // public: Z(){ B::pie(); }
};

class N: public Z { 
    // 不可访问私有继承的基类 apple() pie() pine() 
    // public: N(){ B::apple(); }
};

class F: private B { 
    // 友元类可访问基类私有方法
    public: F(){ B::pine(); }
};

int main()
{
    X x; Y y; Z z; N n; F f;
    x.apple();
    // x.pie();   // 不可外部访问保护成员
    // y.apple(); // 不可访问保护继承的基类
    // z.apple(); // 不可访问私有继承的基类
}
```

上面还将 F 类作为友元引入到 A 类中，这样在 F 类中可以访问 A 类的任意成员，就像是自己的家一样，还可以将 main 函数作为友元引入 A 类，这样在 main 方法中也像在 A 类内一样访问其私有成员。


## ⚡ Override vs. Overwrite

C++ 中有几个常让初学者搞不清晰的术语，通过虚函数表的解析就十分明确：

- Overload 重载，是指在*同作用域*定义*同名*，但*签名不同*的函数，签名包括了参数类型、参数顺序，是否有 const 和 volatile 关键字。
- Override 覆盖，是指在*不同作用域*即在子类中定义和基类*同名*而且*同参数*、*同返回值*的函数，以覆盖*基类虚函数*，与虚函数表关联。
- Overwrite 重写，也叫重定义，是指在*不同作用域*定义和基类*同名*的函数，以实现在作用域上屏蔽同名函数。

注意，签名包括函数名称、参数类型及顺序，后缀关键字如 const 和 volatile，但是不包括返回值！重载解析中不考虑返回类型，而且在不同的作用域里声明的函数也不算是重载。

虽然，函数返回值不作为签名供编译器参考，但是，可以在函数参数列表后面，即圆括号后使用特殊关键来为编译器提供额外参考，例如使用 const 表示 non-mutable 成员函数或叫做常成员函数，否则就是 mutable 函数。常成员函数不改变对象的成员变量. 也不能调用类中任何非 const 成员函数。对于 const 类对象/指针/引用，也只能调用类的 const 成员函数。

其中，*Override* 原意是推翻重来，完全满足虚函数签名条件时，会将函数地址写入父类对应的虚函数表中，并覆盖原始记录，这就表示基类的相应虚函数版本已经从内存中消失了。静态方法不能被重写，因为 static 与 virtual 不能同时使用。子类声明重写的函数时，virtual 关键字省略，本质上都是虚函数属性。

如果签名一至，但返回值不一致，则不能通过编译：重写虚函数返回类型有差异，且不是来自基类的协变类型。所谓协变 Covariant，原意是以保持指定关系不变的方式随另一变量变化的统计数据，You jump and I jump！

重载的虚函数在内存数据布局，在打印出现来的虚函数表中出现的顺序和声明顺序是相反的。

注意，区别 *Override* 与 *Overwrite* 的不同在于，前者是后者的一种特例，而且只对虚函数有意义。前者只会条件完全满足的前提下修改虚函数表中的对应记录，从内存中抹去被覆盖的虚函数，并且其它重载方式也被隐藏。而后者，则只是用在同名不同签名的条件下，将基类的所有同名方法隐藏，不能直接调用，只能通过 Scope operator :: 或 using declarations 来间接调用。

C++11 规范引入了 *override* 和 *final* 关键字，主要作用是提示，在我们下面的代码中有没有发现什么问题呢？

```cpp
class Base {
public:
    virtual void print(void){...}
};

class Derived : public Base {
public:
    void pirnt(void){...}
};
```

额...原来在 Derived 中将 print 误输入为 pirnt，关键问题是编译器完全可以正确的编译上面的代码，这是一个很难发现的错误。

在声明函数时，使用 *override* 关键字就是用来提示编译器，检查覆盖是否正确：

```cpp
struct A
{
    virtual void foo();
    virtual void foonal();
    void bar();
};
 
struct B : A
{
    void foo() const override; // Error: B::foo does not override A::foo
                               // (signature mismatch)
    void bar() override; // Error: A::bar is not virtual
    void foo() override; // OK: B::foo overrides A::foo
    void foonal() final; // OK: B::foonal overrides A::foonal
};

struct C : B
{
    void foonal() override; // Error: can't override a final function B::foonal 
}
```


## ⚡ Scope & Name-Hiding
- Effective C++ 3rd - Item 33: Avoid hiding inherited names.

当编译器在 someFunc 的作用域中遇到名字 x 时，它会先检查 Local Scope 局部作用域，看看是否有什么东西叫这个名字。因为那里有，它们就不再检查其它作用域。

在此例中，someFunc 的 x 类型为 double，而 global x 类型为 int，但这不要紧。C++ 的 name-hiding 规则仅仅是覆盖那个名字，而相对应的名字的类型是否相同是无关紧要的。

在此例中，一个名为 x 的 double 覆盖了一个名为 x 的 int。

```cpp
int x; // global variable
void someFunc()
{
    double x; // local variable
    std::cin >> x; // read a new value for local x
}
```

加入继承以后，在一个派生类成员函数内引用位于基类的数据或成员时，编译器能够找到所引用的东西是因为派生类继承了基类声明的东西。

实际中的运作方法是将派生类的作用域嵌套在基类作用域之中。

以下代码导致的行为会使每一个第一次遇到它的 C++ 程序员吃惊。基于作用域的名字覆盖规则不会有什么变化，基类中的所有名为 mf1 和 mf3 的函数被派生类中的同名函数覆盖。从名字搜索的观点看，Base::mf1 和 Base::mf3 不再被 Derived 继承！

实际上，如果你使用了 public inheritance 但没有继承其它重载函数，就违反了“派生类 is-a 基类”这一基本原则。

在这种情况下，几乎总是要绕过 C++ 对“通过继承得到的名字”的缺省的覆盖机制。那就是使用 Scope Operator :: 直接指定作用域，或者使用 using declarations 来解决。

```cpp
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
    d.mf1(1);       // Error Derived::mf1() hide Base::mf1()
    d.mf3(1);       // Error Derived::mf3() hide Base::mf3()
    d.Base::mf1(2); // OK always
    d.Base::mf3(2); // OK always
}
```

记住：

- ✦ 派生类会隐藏同名的基类成员、数据等。在公共继承下，这不会是想要的。
- ✦ 让被隐藏的名字再次呈现，请使用 using declarations or forwarding functions。


## ⚡ CRTP Static Polymorphism 静多态
- Cee Plus Plus Idioms http://wiki.c2.com/?CeePlusPlusIdioms
- CRTP 编程模式 https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/
- C++ Core Guidelines http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- c++ Patterns https://cpppatterns.com
- Design Patterns in Modern C++ Reusable Approaches for Object-Oriented Software Design by Dmitri Nesteruk
- Hands-On Design Patterns With C++ by Fedor G. Pikus - CH8 The Curiously Recurring Template Pattern
- 奇异递归模板模式(Curiously Recurring Template Pattern) https://zhuanlan.zhihu.com/p/54945314
- https://zh.cppreference.com/w/cpp/memory/enable_shared_from_this
- https://eli.thegreenplace.net/2013/12/05/the-cost-of-dynamic-virtual-calls-vs-static-crtp-dispatch-in-c

静多态是一种比 Dynamic Binding 实现的多态更有效率的多态实现方式。

以下是简单的示范，使用 struct 是因为它默认的访问权为 public，方便写代码，而 class 默认访问权为 private。

```cpp
// static polymorphism demo
template <class impl>
class base : public impl { 
public: void op() { impl::op(); }};

struct impl { void op() {  std::cout<< "work here\n"; }};

base<impl>().op();
```

这是一种编程模式，基于模板参数作为基类的混入模式 Mixin Types。

奇异递归模板模式 CRTP - Curiously Recurring Template Pattern，更一般地被称作 F-bound polymorphism。

CRTP 是 C++ 模板编程时的一种惯用法：把派生类作为基类的模板参数，它在 C++ 中主要有两种用途：

- 实现 Static Polymorphism
- 添加方法同时精简代码

通过 CRTP 实现类似于虚函数的效果，同时又没有虚函数调用开销，因为虚函数调用是 Dynamic Binding，需要通过虚函数指针查找虚函数表进行调用。同时类的对象的体积相比使用虚函数也会减少，因为不需要存储虚函数指针，但是缺点是无法动态绑定。

用以下示范代码演示 CRTP 的形式，关键是使用模板基类：

```cpp
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
    Derived d;
    d.doAction();
}
```

注意这里使用的静态转型，和典型的派生类使用的 *dynamic_cast* 不同，因为这里需要的是静态绑定，使用 *static_cast* 转型就好了，将此视为一种意义暗示。

动态强制转换通常用在运行时，用来保证将派生类正确转型。但在这里不需要这种保证：基类被设计为通过其模板参数继承，编译期绑定。

另外，基类中将默认构造函数定义为 private 防止子类继承时，传入不合规范的其它类型。

事实上，派生类的构造函数必须调用基类的构造函数，即使代码中没有显式调用它，编译器也会默认进行调用。由于基类中的构造函数是私有的，除了友元类之外，不可能访问它，而唯一的友元类是模板类！因此，如果派生类与模板类不同，则代码不会编译，这真是妙用。

还有一个容易忽略的问题，派生类中的方法可能会覆盖相同名称的基类方法。正如 Effective C++ 3rd Item 33: Avoid hiding inherited names 解释的那样，因为这些方法不是虚拟的。因此，您需要注意，基类和派生类中的名称不能相同。


下面演示如何用奇异递归模板模式来简化接口。

假设有一系列传感器，有数据的读写能力，现在希望增加一个数据处理能力，对原始数据进行系数化缩放。

如果，按传统的继承，是不是要给每个传感器都定义一个 scale() 方法？或者增加一层继承，并添加数据处理功能。

但是，使用 CRTP 编程模式真的不要太方便了，直接在模板基类设置一个 scale() 方法就解决了，这操作很有函数式编程的灵活性。但是，这种绕一圈调用本身的方法，缺点是接口定义不够直观。

```cpp
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
public:
    double getValue() const { return 0; };
    void setValue(double value) { };
    // rest of the sensitivity's rich interface...
};

class Sens: public Sensitivity {};

int main()
{
    Sens st;
    st.setValue(1l);
}
```

为何不用非成员的模板函数呢？这是因为会增加额外的代码，至少它的参数更多了，至少要有一个参数，如下：

```cpp
template <typename T>
void scale(T& object, double multiplicator)
{
    object.setValue(object.getValue() * multiplicator);
}
```

标准库的 std::enable_shared_from_this 模板类使用了类似的技术。

假如在 C++ 要在一个已被 shareptr 管理的类型对象内获取并返回 this，为了防止被管理的对象已被智能指针释放，而导致 this 成为悬空指针，可能会考虑以 share_ptr 的形式返回 this 指针。

让需要返回 this 指针的类，继承 std::enable_shared_from_this 模板类，同时模板参数为该类的类型：

```cpp
struct Good: std::enable_shared_from_this<Good>
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
```

参考 enable_shared_from_this 代码：

```cpp
template<class T>
class enable_shared_from_this {
protected:
    constexpr enable_shared_from_this() { }
    enable_shared_from_this(enable_shared_from_this const&) { }
    enable_shared_from_this& operator=(enable_shared_from_this const&) {
        return *this;
    }

public:
    shared_ptr<T> shared_from_this() { return self_; }
    shared_ptr<T const> shared_from_this() const { return self_; }

private:
    weak_ptr<T> self_;

    friend shared_ptr<T>;
};
```

## ⚡ Virtual & Polymorphism 虚拟与多态机制
- Polymorphism in C++ https://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm
- Hands-On Design Patterns With C++ by Fedor G. Pikus - Chapter 1: An Introduction to Inheritance and Polymorphism

C++ 语言中虚函数（virtual function）是在面向对象编程语言中的一个非常重要的概念，虚函数的目的就在于实现多态性。

虚函数的一个重要用法是期待子类对父类的虚拟成员函数进行重载，这种情况下，*virtual* 关键字就意味着“overridable”。当你用一个基类指针指向或引用它的继承类对象的时候，用这个指针或引用去调用虚函数时，实际调用的是继承类的版本。

Effective C++ 提到条款 37: 决不要重新定义继承而来的非虚函数，这是有道理的，统一的约定让代码逻辑更清晰。

因为重载、虚拟、多态机制的存在，编译期编译器在选择要调用的函数版本时有两种方式，Static & Dynamic Binding。那些可以在编译期确定下来的调用，就执行静态绑定 Static Binding，这种方式效率更高，不必在运行时再选择具体要执行的函数版本。

而所谓动态联编，是指在程序的运行阶段动态地选择合适的成员函数，那些不能在编译期确定的调用就需要使用 Dynamic Binding。

多态 Polymorphism 本意就是多种状态，即哪个函数版本会被调用取决于 Dynamic Binding 使用方式。当然，动态绑定只是其中一种实现多态的方法，使用静态绑定也可以实现多态。

Dynamic Binding 使用条件：

1）为基类定义类虚函数；
2）派生子类并实现虚拟函数；
3）使用基类指针指向子类型的对象，并通过它调用虚函数；

虚函数常识：

1）为什么类的静态成员函数不能为虚函数？

虚函数就意味动态绑定，也就是可以在派生类中覆盖，这与静态成员函数的定义（在内存中只有一份拷贝，通过类名或对象引用访问静态成员）本身就是相矛盾的。

2）为什么构造函数不能为虚函数？

因为如果构造函数为虚函数的话，它将会在执行期间被构造，而执行期则意味已经完成对象构造过程，这也是冲突的。构造函数所完成的工作就是为了建立合适的对象，因此在没有构建好的对象上不可能执行多态的工作。在继承体系中，构造的顺序是先构造基类，再构造派生类，其目的就在于确保对象能够成功地构建。构造函数同时承担着虚函数表的建立，如果它本身都是虚函数的话，如何确保 vtbl 的构建成功呢？

3）虚析构函数如何执行？

C++ 开发的时候，用来做基类的类的析构函数一般都是虚函数。当基类中有虚函数的时候，析构函数也要定义为虚析构函数。如果不定义虚析构函数，当删除一个指向派生类对象的指针时，会调用基类的析构函数，而派生类的析构函数未被调用，造成内存泄露。

注意：new 和 delete 是表达式，是静态的成员函数，不能是虚函数。C++ Primer 演示了通过重载类的 operator new, operator delete 来达到类似效果，new Expression versus operator new Function。

只需要在声明函数时使用 *virtual* 关键字，定义函数体时不需要，子类声明中也可以不使用。

虚函数是通过一张虚函数表来实现的，简称 V-Table，它是一块连续的内存，每个内存单元中记录一个 JMP 指令的地址。编译器会为每个有虚函数的类创建一个虚函数表，该虚函数表将被该类的所有对象共享，类的每个虚函数成员占据虚函数表中的一行。

在这个表中，主要是一个类的虚函数的地址表。这张表解决了继承、覆盖的问题，保证其真实反应实际的函数。在有虚函数的类的实例中，分配了指向这个表的指针的内存。所以，当用父类的指针来操作一个子类的时候，这张虚函数表就指明了实际所应该调用的函数。


虚拟机制的基本用法：

- 虚函数，例如：`virtual void imaging() const throw();`
- 纯虚函数，例如：`virtual void pure_virtual() const throw() = 0;`
- 虚继承，例如：`class derive : virtual public base {};`
- 虚解构函数，例如： `virtual ~Shape() throw();`

使用 *virtual* 关键字和纯说明符 *=0* 将方法定义为纯虚函数，*Pure Virtual Functions*，意思是指这个函数为 NULL 指针，除非在类中提供实现定义。所属的类将会变为抽象类，通常作为接口使用，所以纯虚函数一般在子类中提供实现，而不是在其本身，当然可以这样做。

纯说明符或抽象重写说明符只允许在虚函数上使用，它只起形式上的作用，告诉编译系统“这是纯虚函数”。

类声明只要有纯虚函数就会成为抽象类，但是抽象类中除了包含纯虚函数外，还可以提供其它成员函数（虚函数或普通函数）和成员变量。例如，定义 protected 成员函数专供子类使用。

只有类中的虚函数才能被声明为纯虚函数，普通成员函数和顶层函数均不能声明为纯虚函数。

包含纯虚函数的类称为抽象类 *Abstract Class*，之所以说它抽象，是因为它无法实例化，也就无法创建对象。因为作为接口使用，抽象类就是父类，也称为 ABC (Abstract Base Class)。

在大多数 OOP 语言中，都有接口的概念，通常也会有相应的关键字 *interface* 来定义一个接口，使用 *implements* 关键字来实现接口。本质上，接口是一种约定规范，目录是为子类提供一个统一的规范。从这一点来说，即使用没有 *interface* 关键字，使用 *class* 也可以定义一个具有实质意义的接口。

某些类，主要是接口这样的类，在现实角度和逻辑角度都不需要实例化（不需要创建它的对象实例），它的存在目的就是提供一个形式上的接口，让子类按同一规范来实现，C++ 抽象类的目的也就是提供接口定义。

一般上，多继承机制会带来复杂的问题，一个类继承多个基类本身就是复杂的结构。但是一个类可以有多个接口，这是很正确的做法。接口相当于定义了一套行为，实现相应的接口就具有这套行为规范的能力。像鸵鸟困局这样的问题也可以很好地解决，像 Golang 语言那样使用接口组合来扩展类的能力。

以继承为特点的 OOP 只是编程世界的一种抽象方式，在 Golang 的世界里没有继承，只有组合和接口，并且是松散的接口结构，不强制声明实现接口。

If it looks like a duck, swims like a duck, and quacks like a duck, then it probably is a duck.

翻译过来就是：如果某个东西长得像鸭子，像鸭子一样游泳，像鸭子一样嘎嘎叫，那它就可以被看成是一只鸭子。

结合到 GO 语言，也就是说那些实现了鸭子某个 interface 全部方法的 struct 对象就是鸭子。

单一继承关系解决了 is-a 也就是定义问题，因此可以把子类当做父类来对待。但对于父类不同但又具有某些共同行为的数据，单一继承就不能解决了，C++ 采取了多继承这种复杂的方式。。

所以，在 C++ 编程中，Multiple and Virtual Inheritance，Virtual Functions 的关系处理是逃不掉的，这是高级内容。

以下代码可以用来测试构造函数和析构的执行顺序：

```cpp
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
    std::cout << "\n======nonvirtual inheritence=======\n";
    MI mi;
    std::cout << "\n========virtual inheritence========\n";
    MIV miv;
}
```

Output: 

    ======nonvirtual inheritence=======
    A() B() C() X() Y() Z() MI() 
    ========virtual inheritence========
    X() Y() Z() A() B() C() MIV() 

- FAQ 20.05 What happens when a destructor is executed?
- FAQ 20.06 What is the purpose of a copy constructor?

析构器会自动调用所有成员对象和所有立即非虚拟基类的析构函数。首先，析构函数体执行，然后以成员对象在类主体中出现的相反顺序调用成员对象的析构函数，然后调用立即基类的析构函数，以继承它们时在类声明中出现的反向顺序进行。

虚拟基类是特殊的，它们的析构函数在大多数派生类的析构函数末尾调用。这是因为，虚拟继承机制改变了原有的构造器执行顺序，在继承列表中的基类中，按虚基类优先，从左到右，从顶级到底层的顺序执行。总之，virtual 继承出现的位置，其基类就会优先执行构造过程。

可以在以上代码的 MI 和 MIV 继承列表中差别，只是后者将继承 Z 的方式改为 virtual 进行测试。

使用虚继承后，导致编译器通过继承列表先找到 Z 的顶层基类即 X -> Y -> Z 这样的优先顺序执行构造过程，然后到 A -> B -> C 。

原本是优先处理 C 的继承链，从其顶层基类开始，按 A -> B -> C 这样的顺序执行构造过程，然后再到 X -> Y -> Z。

参考 The C++ Programming Language 3rd/4th 两个版本中关于 Class Hierarchies 的两个示范代码：

```cpp
class A {                  /*no constructor*/ };
class B { public: B();     /*default constructor*/ };
class C { public: C(int) ; /*no default constructor*/ };
class D : virtual public A, virtual public B, virtual public C
{
    D() { /* ... */ } // error: no default constructor for C
    D(int i) : C(i) { /* ... */ }; // ok 
};
// The C++ Programming Language, Third Edition
// 15.2.4.1 Programming Virtual Bases [hier.vbase.prog]

struct V 
{
    V(int i); // no default constructor
};
struct A 
{
    A(); // default constructor
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
    D() { /* ... */ } // error : no default constructor for C or V
    D(int i) :C{i} { /* ... */ }; // error : no default constructor for V
    D(int i, int j) :V{i}, C{j} { /* ... */ } // OK
};
// The C++ Programming Language, Forth Edition
// 21.3.5.1 Constructing Virtual Bases
```

这两个示范代码都是在说多继承中的构造过程问题，要使用一个多继承层次结构成功执行构造，就必需满足所有基类相应的构造函数被成功执行。

而这个过程中，C++ 构造器会执行一些*默认构造函数*，即没有参数的构造函数。如果没有定义任何构造函数，那么编译器会隐含提供一个，这个隐含的动作就是 compiler-synthesized。除非代码中定义了任何一个构造函数，此时隐含提供的默认构造函数就不存在了。

这就是说，像 struct V 这样的定义了一个带整数参数的构造函数，就不能对它调用默认构造函数，即需要显式指定要执行的构造函数。

而 struct A 显式定义了默认构造函数，所以编译器会和调用隐含的默认构造函数一样，在需要时自动调用它。


## ⚡ Virtual and Multiple Inheritance
- C++ Primier 4th - Advanced Topics - 17.3. Multiple and Virtual Inheritance
- C++ Primer Plus 6th - 14 Reusing Code in C++ - Multiple Inheritance
- Inside the C++ Object Model By Stanley B. Lippman, May 03, 1996
- Thinking in C++ 2nd Volume 2: Standard Libraries & Advanced Topics
- The C++ Programming Language 3rd - II Abstraction Mechanisms - 15.2.4.1 Programming Virtual Bases
- The C++ Programming Language 4th - III Abstraction Mechanisms - 21.3.5.1 Constructing Virtual Bases

在派生类继承基类时，加上 virtual public 关键词则为虚拟继承，是多重继承的一种形式，派生类多次共享包含在层次结构中的基类的单个副本。

虚继承与多继承示范代码片段：

```cpp
// Virtual Inheritance
class Base {};
class Derived : virtual public Base {};
// class Derived : public virtual Base {}; 
// virtual and public can appear in either order

// Multiple Inheritance
class HumanBeing {
public:
    virtual void pure_virtual() const throw() = 0;
    virtual void Show() {}
    virtual ~HumanBeing() {}
}
class Waiter : public HummanBeing { public: void Show() {} };
class Singer : public HummanBeing { public: void Show() {} };
class SingingWaiter : public Waiter, public Singer {...};
// class SingingWaiter : public Waiter, Singer {...}; // Singer is a private base
```

根据上面的代码，先来搞清楚两个容易混淆的概念：

- VBC - Virtual Base Classes，此处 Base 就称为虚基类，这是相对于子类 Derived 派生方式而言的，虚基类本身可以是一个普通的类。
- ABC - Abstract Base Classes，当父类中存在至少一个纯虚函数时，这个类就是抽象类，它作为基类使用时就是 ABC。

这里主要关注虚继承与多继承，相对于单继承，使用多继承是件复杂的事，它带来两大问题：

- 二义性：不同的父类拥有名字相同的成员时，如何处理二义性，Ambiguous upcasting？
- 多副本：通过多个直接基类继承共同基类的多个实例，即内存有多个 HumanBeing 副本，Duplicate subobjects 如何处理以节省内存？

所以，有人强烈反对使用多继承，但也有人钟爱有加，形成 MI vs SI 两大阵营。

在典型的多继承菱形结构中，如上面的 SingingWaiter，有两个直接基类和一个共同基类 HumanBeing。实例化时，SingingWaiter 实例就会包含多个基类实例，在这里就是有两个 HumanBeing，分别位于 Waiter 和 Singer 父类内部，它们有相应的地址。

以下展示了二义性问题，以及显式转型处理方式：

```cpp
SingingWaiter ed;
HumanBeing * ph = &ed; // error: ambiguous
ed.Show(); // error: ambigous
ed.Singer::Show(); // OK: use Singer version
ed.Waiter::Show(); // OK: use Waiter version

HumanBeing * p1 = (Waiter *) &ed; // OK: the HumanBeing in Waiter
HumanBeing * p2 = (Singer *) &ed; // OK: the HumanBeing in Singer
Waiter *pw = &ed;                 // OK: the SingingWaiter upcasting as a Waiter
Singer *ps = &ed;                 // OK: the SingingWaiter upcasting as a Singer
```

二义性有两种基本方式解决，一是使用 Scope Operator :: 来调用同名的继承方法指定版本，或使用 using declarations 如 `using Singer::Show;`。另一个方法就是使存在歧义的成员只在一条继承路径上出现，而最接近的版本就是默认被调用的版本，更好的方法是提供自己的版本。

Table 14.1 Varieties of Inheritance 展示了各种基本继承关系中父类成员在子类中的访问权：

|  Base's Property   | Public Inheritance | Protected Inheritance | Private Inheritance |
|--------------------|--------------------|-----------------------|---------------------|
| Public members     | Public members     | Protected members     | Private members     |
| Protected members  | Protected members  | Protected members     | Private members     |
| Private members    | NO                 | NO                    | NO                  |
| Implicit upcasting | Yes                | Yes (within)          | No                  |

注意，public 继承方式是完全支持隐式转型的，所以上面的代码中可以直接将 SingingWaiter 的指针赋值给 Waiter 或 Singer 指针。

这也是多继承问题的关键点之一，编译器偷偷做了一件事情：this 指针调整！

在单继承 SI 模型下，对象内存采用重叠的模型，基类和任何的派生类的指针都指向该对象的首地址。因此，转型操作不影响指针指向，这些指针的地址值都一样，所有基类都共享同一个首地址。

也就是说，在单继承体系内，不论你用什么样的方式对其中一个指针进行 downcasting 或 upcasting，指针的地址值都是一样的。

但是在 MI 的世界里，采用的是非重叠模型。

简单来说，对于子类实例，其包含的每个基类的对象都有自己的首地址，只有继承列表中第一个基类对象地址才一样。

所以，在频繁的 this 指针调整中，this 指针地址变化主要发生在派生类对象与其继承列表中第 2 个以及后续的基类对象之间的转换。

参考 1996 年发行的 Inside the C++ Object Model By Stanley B. Lippman，Chapter 3. The Semantics of Data - 3.4. Inheritance and the Data Member。

如果在多条继承路径上有一个公共的基类，在这些路径中的某几条汇合处，即这个*公共基类*就会产生多个实例，若只想保存这个公共基类的一个实例，就需要对这个公共基类使用*虚继承*，将公共基类当作虚基类 VBC - Virtual Base Classes。

在多继承情况下，从不同途径可以能继承得到同名的数据成员，这在内存中有不同的拷贝会造成数据不一致问题。C++ 使用虚拟继承 Virtual Inheritance，将共同基类设置为虚基类。这时从不同的路径继承过来的同名数据成员在内存中就只有一个拷贝，同一个函数名也只有一个映射。通过虚基类统一多基类继承的同名数据成员解决了二义性问题，也节省了内存，避免了数据不一致的问题。

如果是虚继承、非虚继承混搭，基类有多少子对象，就要按组合来计算，虚继承的部分算一个，其它继承的有几个算几个。

加入虚继承，就需要修改原有代码，即使用在 C++ 的编译规则上也做了调整。如果是在工业上，这是潜在的工作量，和回收返工操作没什么不同：

```cpp
class Singer : virtual public HumanBeing {...};
class Waiter : public virtual HumanBeing {...};
class SingingWaiter: public Singer, public Waiter {...};
```

按以上修改声明后，加入了虚继承，这样实例化 SingingWaiter 就只会继承到一个 HumanBeing 实例。关键字 virtual 的位置可前可后，它的作用就是将 C++ 菱形多继承结构中共同基类作为子类的直接基类一样看待，即 HumanBeing 相当于 SingingWaiter 的直接基类。

                +============+
                | HumanBeing |
                +=====+======+
                 /   v|i    \
                /    i|n     \
    +========+ /     r|h      \ +========+
    | Waiter |+      t|e       +| Singer |
    +========+ \     u|r      / +========+
                \    a|i     /
                 \   l|t    /
               +===============+
               | SingingWaiter |
               +===============+

        C++ Diamond Inheritance Hierarchy

以上示意图也说明了虚继承的关于构造器规则的调整中，具有间接虚拟基类的派生类应该让其构造函数直接调用间接基类构造函数，这对于间接非虚拟基类是非法的。非虚继承中，只有直接基类的构造器才可以出现在子类构造器的 Initialization list，不能是间接基类的构造器。

这个规则的调整，是因为在虚继承关系中，如果 SingingWaiter 直接基类都在其构造器中的初始化列表中执行虚基类的构造器，那么会出现多个路径通向虚基类的构造器，这与虚继承的设计规则相违背。

```cpp
SingingWaiter(const Worker & man, int p = 0, int v = Singer::other)
: Waiter(man,p), Singer(man,v) {} // flawed

SingingWaiter(const Worker & man, int p = 0, int v = Singer::other)
: Worker(man), Waiter(man,p), Singer(man,v) {}
```

上面代码的第一种方式，如果在非虚继承模式下，初始化参数 man 可以经由 SingingWaiter 的父类传递到上一层基类。但是在虚承继模式下，这种做法就被禁止了。因为此时虚基类只有一个对象，所以需要先对虚基类进行构造，这就是为何可以在 SingingWaiter 的构造器中调用虚基类的构造器。

如果虚基类不只有默认构造器，那么就应该在子类 SingingWaiter 的构造器中显式调用，这样做才保证虚基类只有一个对象。

虚拟基类的使用并没有那么简单，上面的示例使用默认构造函数，包括隐含编译器合成的或显式定义的。如果虚拟基有一个构造函数，事情就会变得有点奇怪。

需要引入一个新术语来简化理解：most-derived，最近派生类，通常是指所执行的构造函数所在的类，它的构造器只能执行直接基类的构造函数。但是使用虚继承后，这个概念也指对虚基类进行初始化的类。参考前面的棱形层次结构示意图，在虚继承方式下，无论子类离虚基数间隔多远，子类都可以对虚基类进行初始化。

参考以下示范代码，VMan1 和 VMan2 对直接基类 HumanBeing 初始化是很正常的，而 MI 或 XMan 在虚继承形式下也可以对远端的虚基类进行初始化：

```cpp
class HumanBeing 
{
public:
    HumanBeing() {}
    HumanBeing(int) {}
    // pure virtual make it to be an abstract class
    virtual const char* vf() const = 0;
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
    XMan() : HumanBeing(4) {}
};
```

像上面这样的多继承结构中，二义性问题就比较复杂。HumanBeing、VMan1、Vman2 同时定义了 vf() 函数，继承者覆盖了顶层基数的虚函数，因为子类中出现了和基类虚函数同名又同签名的形式。

但是接下来，MI 如何要多继承 VMan1、Vman2 就会出现，两个直接基类有相同签名的虚函数，如果不是两个基类都使用了虚继承，MI 可以真的继承它们，而无需覆盖虚函数 vf()。在两者都使用虚继承时，MI 如果不覆盖 vf()，编译器就不知道怎么处理二义性问题。

这是因为从 HumanBeing 到 MI 之间，vf() 函数有二条继承路线，从 VMan1 或者从 VMan2，这就导致：no unique final overrider。在 MSVC 中的提示就是直接基类同名方法不明确继承，这是典型的棱形继承二义性问题 Diamond Problem。

至于为何一定要 MI 继承 vf() 函数呢，不继承行吗？不行，至少在这种情况下不行。这是因为虚继承必需将虚基类的方法继承给子类，否则就失去虚继承的设计意义了。

另外，给虚基类进行初始化并不是用户友好的一种方式，对于代码的用户来说深入了解继承链是件乏味浪费时间的事。

因此，使用默认参数是个好方法：

```cpp
class HumanBeing {
public:
    // Default constructor removes responsibility:
    HumanBeing(int = 0) {}
    virtual char* vf() const = 0;
    virtual ~HumanBeing() {}
};
```

- FAQ 21.14 How can the compiler be kept from generating duplicate outlined copies of inline virtual functions?

如果类具有一个或多个虚函数，继承的或在该类中声明的，则该类应至少具有一个非内联虚拟函数。许多编译器使用第一个非内联虚拟函数的位置来确定源文件，该文件将包含类的神奇内容（virtual table, out-lined copies of inline virtual functions）。如果类的所有虚拟函数都是内联定义的，那么这些编译器可能会在那些包含此类头文件的每个源文件中放置神奇内容的静态副本。

请注意，此建议对编译器相当敏感。一些编译器不会生成神奇内容的副本，即使类中的所有虚拟函数都是内联的。但即使在这些编译器中，也不需要花费太多的成本确保至少有一个类的虚拟函数是非内联的。

相比普通函数，调用虚函数的额外开销是不大的。实际上，几乎所有编译器都以相同的方式进行编译，并且开销非常小。并且在参数越多的情况下，越趋于相同，因为虚函数的动态绑定是恒定的开销。在极大的差别情况下，可能有 10% - 20% 的额外开销。


## ⚡ Class Layout 类数据结构布局
- C++ vtables https://shaharmike.com/cpp/vtable-part1/
- Inside the C++ Object Model By Stanley B. Lippman, May 03, 1996
- the Virtual Table https://www.learncpp.com/cpp-tutorial/the-virtual-table/

类数据结构在内存布局上有两种策略，取决于编译器的实现，它们决定了虚函数表在内存中地址如何安排：

- Virtual Inheritance with Pointer Strategy
- Virtual Inheritance with Virtual Table Offset Strategy

根据使用的继承机制不同，编译器不实现差异，类数据内存布局明显有变化，主要包含了：

- vftable 虚函数表：包含虚函数的列表数据结构；
- vbtable 虚基类表：继承链上所有路径上共同的虚基类都通过一张表管理；
- vfptr 虚函数指针：指向虚函数表中的首条目；
- vbptr 虚基类指针：指向虚基类副本，在使用虚继承时产生；
- this adjustor 上下文指针调整：继承结构中，有各种类实例对象需要使用 this 指针来访问成员，根据进行偏移地址调整；

显然，创建类实例后，它就是按类结构存放在内存某个区块的数据结构，任意多的实例就有任意多的这些数据结构。但是类的结构是统一的，除了实例的数据，像成员函数、静态成员这些东西都是共用的。所以设置数据结构时，就需要使用一个 this 指针来指向这些数据，并且在实例数据所在要保留一个指针指向类的公共结构。当调用成员时，就根据数据找到到成员方法的地址，或者对于虚函数，就先通过虚函数表指针来定位。所以，虚函数表有时也被叫作 dispatch table，派发函数调用的表。调用成员方法时，this 指针作为第一个参数传入，供成员函数访问相应的实例数据。

以下示范代码中，表示了编译器隐含的操作，它会在顶层基类内存开始地址处放置一个虚函数表指针：

```cpp
class Base
{
public:
    VirtualTable* __vptr;
    virtual void function1() {};
    virtual void function2() {};
};
```

在 MSVC 编译器中，一个类使用虚函数表方式如下，根据单一继承、多继承，和是否使用虚继承进行区别，这里只讨论两层继承：

- 非虚单继承，只要类本身或父类只要使用了虚函数，就需要使用一张虚函数表，表中条目按虚函数在类中的声明顺序排列，基类优先，包括私有的虚函数；
- 虚单一继承，只要类本身或父类只要使用了虚函数，都独立一张虚函数表管理，因没有其它基类，所以子类不用和其它非虚基类共用虚函数表。
- 非虚多继承，子类和首个使用了虚函数的基类共用虚函数表，其它基类使用独立虚函表，如果有使用虚函数；

虚拟多继承情形分开讨论，主要区别在于是否使用虚继承，如果使用虚继承，类本身和基类虚函数分表管理。所有可能存在的虚基类都通过一张 vbtable 表管理。

- 子类、基类都没有使用虚函数的虚继承很简单，只有 vbtable 来管理虚基类，没有虚函数表，因为不需要。
- 只在子类使用虚函数的情况，只有子类一张虚函数表。
- 只在基类使用虚函数的情况，根据使用了虚函数的基数在列表的顺序设置虚函数表。因为只会有一张 vbtable，只有在第一个虚继承的基类的虚函数表前放置，如果它有使用虚函数表。
- 子类、基类都有使用虚函数的情况，子类会和虚继承前面的基类共同同一张虚函数表，如果前面有使用了虚函数的基类。后继的基类按继承列表顺序设置虚函数表。会在第一个虚基类的虚函数表前会设置一张 vbtable，和其它虚基类共用。

在多层的虚拟继承结构中，vbtable 会有多张，取决于有多少层次深度，和虚继承关系数量。

各种现代编译都提供了打印 C++ 类对象数据内存布局的工具：

    cl.exe source.cpp /d1reportSingleClassLayout<CLASSNAME>
    cl.exe source.cpp /d1reportAllClassLayout
    gcc --fdump-class-hierarchy source.cpp
    clang -Xclang -fdump-record-layouts source.cpp

输出格式不一样，以 MSVC 编译器的输出为参考，将前面小节的示范类型层次结构打印出来，以下是没有虚继承时两层继承的内存布局：

    **********************************************************************
    ** Visual Studio 2019 Developer Command Prompt v16.6.1
    ** Copyright (c) 2020 Microsoft Corporation
    **********************************************************************
    [vcvarsall.bat] Environment initialized for: 'x64'
    用于 x64 的 Microsoft (R) C/C++ 优化编译器 19.26.28806 版
    版权所有(C) Microsoft Corporation。保留所有权利。

    class XMan  size(16):
        +---
     0  | +--- (base class MI)
     0  | | +--- (base class VMan1)
     0  | | | +--- (base class HumanBeing)
     0  | | | | {vfptr}
        | | | +---
        | | +---
     8  | | +--- (base class VMan2)
     8  | | | +--- (base class HumanBeing)
     8  | | | | {vfptr}
        | | | +---
        | | +---
        | +---
        +---

    XMan::$vftable@VMan1@:
        | &XMan_meta
        |  0
     0  | &MI::vf 
     1  | &XMan::{dtor} 

    XMan::$vftable@VMan2@:
        | -8
     0  | &thunk: this-=8; goto MI::vf 
     1  | &thunk: this-=8; goto XMan::{dtor} 

    XMan::{dtor} this adjustor: 0
    XMan::__delDtor this adjustor: 0
    XMan::__vecDelDtor this adjustor: 0

从打印出来的内存布局信息可以看到，HumanBeing 有两个副本对象。XMan 实例主体占 16-Byte，包含自身的数据成员和两个直接基类的数据成员。因为使用了虚函数，所以配置了相应的 Virtual Table，每个直接父类对应一个，使用 vfptr 指针引用。

包含纯虚函数的基类 HumanBeing 是抽象类，不能直接使用代码来实例化，所以 MSVC 没有打印相应的内存布局，只嵌入子类的内存布局中。

其它普通的类方法成员有专用的地址，不会在虚表中记录，也不会在对象的数据内存布局中记录。

特定情况可以看到虚函数表中有两个析构函数，在 MSVC 生成的内存布局信息中会用 deleting 和 complete 后缀标记，因为对象有两种构造方式，栈构造和堆构造。所以对应对象也有两种析构方式。差别在于，堆上对象的析构需要手动管理，而栈内存的对象析构不需要执行 delete 函数，编译器会自动处理回收问题。

以下是两层的虚继承的类数据结构，同时有两张 vbtable 对应两个直接基类的虚继承。最主要的是 HumanBeing 在内存中只有一个副本，这就是虚继承的设计的目的：

    class XMan  size(32):
        +---
     0  | +--- (base class MI)
     0  | | +--- (base class VMan1)
     0  | | | {vbptr}
        | | | <alignment member> (size=4)
        | | +---
     8  | | +--- (base class VMan2)
     8  | | | {vbptr}
        | | | <alignment member> (size=4)
        | | +---
        | | <alignment member> (size=4)
        | +---
        | <alignment member> (size=4)
        +---
    20  | (vtordisp for vbase HumanBeing)
        +--- (virtual base HumanBeing)
    24  | {vfptr}
        +---

    XMan::$vbtable@VMan1@:
     0  | 0
     1  | 24 (XMand(VMan1+0)HumanBeing)

    XMan::$vbtable@VMan2@:
     0  | 0
     1  | 16 (XMand(VMan2+0)HumanBeing)

    XMan::$vftable@:
        | -24
     0  | &(vtordisp) MI::vf 
     1  | &(vtordisp) XMan::{dtor} 

    XMan::{dtor} this adjustor: 24
    XMan::__delDtor this adjustor: 24
    XMan::__vecDelDtor this adjustor: 24
    vbi:       class  offset o.vbptr  o.vbte fVtorDisp
          HumanBeing      24       0       4 1

GCC 编译器，可以使用 -fdump-class-hierarchy 选项进行编译会得到一个 .class 类结构信息文件，以下是同样源代码产生类层次布局，只摘取 XMan 相关部分。

在虚继承中，GCC 编译器还会为子类多生成一个虚表数据表 VTT(virtual table table)，这张表记录了虚继承类的虚表地址。

显示，两种编译器处理虚函数的工作方式完全不同：

    VTT for XMan
    XMan::_ZTT4XMan: 10u entries
    0     ((& XMan::_ZTV4XMan) + 20u)
    4     ((& XMan::_ZTC4XMan0_2MI) + 20u)
    8     ((& XMan::_ZTC4XMan0_5VMan1) + 20u)
    12    ((& XMan::_ZTC4XMan0_5VMan1) + 20u)
    16    ((& XMan::_ZTC4XMan4_5VMan2) + 20u)
    20    ((& XMan::_ZTC4XMan4_5VMan2) + 48u)
    24    ((& XMan::_ZTC4XMan0_2MI) + 20u)
    28    ((& XMan::_ZTC4XMan0_2MI) + 52u)
    32    ((& XMan::_ZTV4XMan) + 20u)
    36    ((& XMan::_ZTV4XMan) + 52u)

    Class XMan
       size=8 align=4
       base size=8 base align=4
    XMan (0x0x5c4b040) 0
        vptridx=0u vptr=((& XMan::_ZTV4XMan) + 20u)
      MI (0x0x5c4b080) 0
          primary-for XMan (0x0x5c4b040)
          subvttidx=4u
        VMan1 (0x0x5c4b0c0) 0 nearly-empty
            primary-for MI (0x0x5c4b080)
            subvttidx=8u
          HumanBeing (0x0x5c423f0) 0 nearly-empty virtual
              primary-for VMan1 (0x0x5c4b0c0)
              vptridx=32u vbaseoffset=-20
        VMan2 (0x0x5c4b100) 4 nearly-empty
            lost-primary
            subvttidx=16u vptridx=36u vptr=((& XMan::_ZTV4XMan) + 52u)
          HumanBeing (0x0x5c423f0) alternative-path

    Vtable for XMan
    XMan::_ZTV4XMan: 16u entries
    0     0u
    4     0u
    8     0u
    12    (int (*)(...))0
    16    (int (*)(...))(& _ZTI4XMan)
    20    (int (*)(...))MI::vf
    24    (int (*)(...))XMan::~XMan
    28    (int (*)(...))XMan::~XMan
    32    4294967292u
    36    4294967292u
    40    4294967292u
    44    (int (*)(...))-4
    48    (int (*)(...))(& _ZTI4XMan)
    52    (int (*)(...))MI::_ZThn4_NK2MI2vfEv
    56    (int (*)(...))XMan::_ZThn4_N4XManD1Ev
    60    (int (*)(...))XMan::_ZThn4_N4XManD0Ev

    Construction vtable for MI (0x0x5c4b080 instance) in XMan
    XMan::_ZTC4XMan0_2MI: 16u entries
    0     0u
    4     0u
    8     0u
    12    (int (*)(...))0
    16    (int (*)(...))(& _ZTI2MI)
    20    (int (*)(...))MI::vf
    24    0u
    28    0u
    32    4294967292u
    36    4294967292u
    40    4294967292u
    44    (int (*)(...))-4
    48    (int (*)(...))(& _ZTI2MI)
    52    (int (*)(...))MI::_ZThn4_NK2MI2vfEv
    56    0u
    60    0u

    Construction vtable for VMan1 (0x0x5c4b0c0 instance) in XMan
    XMan::_ZTC4XMan0_5VMan1: 8u entries
    0     0u
    4     0u
    8     0u
    12    (int (*)(...))0
    16    (int (*)(...))(& _ZTI5VMan1)
    20    (int (*)(...))VMan1::vf
    24    0u
    28    0u

    Construction vtable for VMan2 (0x0x5c4b100 instance) in XMan
    XMan::_ZTC4XMan4_5VMan2: 15u entries
    0     4294967292u
    4     0u
    8     0u
    12    (int (*)(...))0
    16    (int (*)(...))(& _ZTI5VMan2)
    20    (int (*)(...))VMan2::vf
    24    0u
    28    0u
    32    4u
    36    4u
    40    (int (*)(...))4
    44    (int (*)(...))(& _ZTI5VMan2)
    48    (int (*)(...))VMan2::_ZTv0_n12_NK5VMan22vfEv
    52    0u
    56    0u

