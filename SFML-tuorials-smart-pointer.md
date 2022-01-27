
# 🚩 Smart Pointers
- http://zh.highscore.de/cpp/boost/smartpointers.html
- C++ 是否应避免使用普通指针，而使用智能指针 shared，unique，weak https://www.zhihu.com/question/319277442/answer/1517987598

内容：

    2.1 概述
    2.2 RAII
    2.3 作用域指针
    2.4 作用域数组
    2.5 共享指针
    2.6 共享数组
    2.7 弱指针
    2.8 介入式指针
    2.9 指针容器

Boost 提供了下面几种智能指针：

| shared_ptr<T>    | 普通的智能指针，大多数地方都使用 shared_ptr。                                 |
| scoped_ptr<T>    | 作用域指针，它不传递所有权，离开作用域能够自动释放。                          |
| intrusive_ptr<T> | 比 shared_ptr 更好的智能指针，但是需要类型 T 提供自己的指针使用引用记数机制。 |
| weak_ptr<T>      | 一个弱指针，帮助 shared_ptr 避免循环引用。                                    |
| shared_array<T>  | 和 shared_ptr 类似，用来处理数组。                                            |
| scoped_array<T>  | 和 scoped_ptr 类似，用类处理数组。                                            |

Boost C++ 库 Smart Pointers 提供了许多可以用在各种场合的智能指针。

智能指针的原理基于一个常见的习语叫做 RAII - Resource Acquisition Is Initialization 资源申请即初始化。 智能指针只是这个习语的其中一例——当然是相当重要的一例。 智能指针确保在任何情况下，动态分配的内存都能得到正确释放，从而将开发人员从这项任务中解放了出来。 这包括程序因为异常而中断，原本用于释放内存的代码被跳过的场景。 用一个动态分配的对象的地址来初始化智能指针，在析构的时候释放内存，就确保了这一点。 因为析构函数总是会被执行的，这样所包含的内存也将总是会被释放。

无论何时，一定得有第二条指令来释放之前另一条指令所分配的资源时，RAII 都是适用的。 许多的 C++ 应用程序都需要动态管理内存，因而智能指针是一种很重要的 RAII 类型。 不过 RAII 本身是适用于许多其它场景的。

## ⚡ lvalue & rvalue reference
- https://www.geeksforgeeks.org/lvalues-references-and-rvalues-references-in-c-with-examples/

左值（lvalue）和右值（rvalue）是比较基础的概念，虽然平常几乎用不到，但 C++11 之后变得十分重要，它是理解 move/forward 等新语义的基础。

左值与右值这两个概念是从 C 中传承而来的，左值指既能够出现在等号左边，也能出现在等号右边的变量；右值则是只能出现在等号右边的变量。

左值和右值主要的区别之一是左值可以被修改，而右值不能。左值是可寻址的变量，有持久性。右值一般是不可寻址的常量，或在表达式求值过程中创建的无名临时对象，短暂性的。

左值引用是一个类型变量的别名，如 &a = b 表示的 a 和 b 是同一个变量，a 和 b 表现在内存中相同的地址。

右值是只能放在赋值右边的值, 右值没有变量名字, 如 i+j 两个变量相加这个表达式返回的值，放在一个临时内存空间, 这个空间并不能被用来赋值，可以看作一个常量。例如，不能写 i+j = 5 这样的赋值表达式。

但是在 C++11 的右值引用出现后就改变了。

为了支持移动语义减少内存拷贝以优化性能，实现移动构造函数和移动赋值函数，Move Constructors & Move Assignment Operators，，C++11 引入了右值引用，用来自由接管右值引用的对象内容。也就是通过右值引用实现将右值变成左值，即将没有变量名的右值变成了有名有姓的变量。

例如 String 类内部都有一个 char * pstr 指针指向实际存放字符串的内存，以下代码片段有 str1, str2, str3 三个 String 对象：

    str3 = str1.concat(str2);

上面的代码实际执行了二次构造函数, 第一次是 concat() 函数内构造一个临时字符串对象, 第二次是赋值的时候执行了拷贝构造函数，临时对象的值被拷贝到 str3 的内存, 然后临时对象立即被销毁。

显然这个第二次拷贝构造造成了多余的消耗，有了右值引用后就可以增加一个移动构造函数以及移动赋值函数来解决这个问题，直接把临时值拿来用，而不再复制一次，然后把 other.pstr 置 null 避免析构函数 delete pstr:

    String(String &&other) {
        pstr = other.pstr;
        other.pstr = nullptr;
    }

以下代码显示左值引用与右值引用：

```cpp
#include <iostream>  // for std::cout & std::endl
#include <utility>   // for std::move()
#include <string>    // for std::string
#include <cstdlib>   // for EXIT_SUCCESS macro

using namespace std;

void foo(const std::string& str)
{
    cout << "foo(const std::string& str) (const lvalue ref):\t" << str << endl;
}
 
void foo(std::string& str)
{
    cout << "foo(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void foo(std::string&& str)
{
    cout << "foo(std::string&& str) (rvalue ref):\t" << str << endl;
}
 
void baz(const std::string& str)
{
    cout << "baz(const std::string& str) (const lvalue ref):\t" << str << endl;
}
 
void baz(std::string& str)
{
    cout << "baz(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void bar(std::string& str)
{
    cout << "bar(std::string& str) (non-const lvalue ref):\t" << str << endl;
}
 
void constObjectCallFunc(std::string&& str)
{
    cout << "constObjectCallFunc(std::string&& str) (rvalue ref):\t" << str << endl;
}

int main()
{
    std::string hello("Good Bye!");
    const std::string final("FINAL!");

    // Declaring lvalue reference
    string& lref = hello;
 
    // Declaring rvalue reference
    string&& rref = "some rvalue";
 
    // error: as l-value cannot be assigned to the r-value references
    // string &&ref = hello;
 
    // foo(std::string& str) will be called
    foo(hello);
 
    // foo(std::string&& str) will be called
    foo(std::string("Hello"));
    foo(std::move(hello + " using std::move()"));
 
    cout << "\n\n";
 
    // move semantics fallback
    // baz(const std::string& str) will be called
    baz(std::string("This is temporary string object"));
    baz(std::move(std::string("This is temporary string object using std::move()")));

    // baz(const std::string& str) will be called
    baz(final);
    // baz(std::string& str) will be called
    baz(hello);

    cout << "\n\n";
 
    std::string failToCall("This will fail to call");
 
    /*
      Reasons to fail bar() call -
      1. No rvalue reference implementation available
      2. No const lvalue reference implementation available
      */
    // bar(std::move(failToCall));
 
    // constObjectCallFunc(std::move(final));
    // Error : because of const qualifier
    // It doesn't make any sense to steal or
    // move the resources of a const object
   
    return EXIT_SUCCESS;
}
```

std::move 和 std::forward 是 C++11 中的特性，用于解决 C++98/C++0x 中遗留的问题，move 用来将左值转换成右值。 所谓转发 forward 就是通过一个函数将参数继续转交给另一个函数进行处理，原参数可能是右值，可能是左值，如果还能继续保持参数的原有特征，那么它就是完美转发。下面的例子 std::forward 结合模板编程实现：

    #include <iostream>

    void process_(int& i){
        std::cout << "process_lvalue_reference ... " << i << std::endl;
    }

    void process_(int&& i){
        std::cout << "process_rvalue_reference ... " << i << std::endl;
    }

    template<typename T> 
    void forward_(T&& i){
        process_(std::forward<T>(i));
    }

    int main()
    {
        int i = 0;
        process_(i);            // process_lvalue_reference ... 0
        process_(1);            // process_rvalue_reference ... 1
        process_(std::move(i)); // process_rvalue_reference ... 0
        forward_(i);            // process_lvalue_reference ... 0
        forward_(std::move(i)); // process_rvalue_reference ... 0
    }


## ⚡ Move Constructors 
- Move Constructors https://en.cppreference.com/w/cpp/language/move_constructor
- move Assignment Opertors https://en.cppreference.com/w/cpp/language/move_assignment
- https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/
- https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170

Move Constructors 和 Move Assignment Operators 是 C++11 基于移动语义引入的两项提供效率的技术。

```cpp
class-name ( class-name && )    (1) (since C++11)
class-name ( class-name && ) = default; (2) (since C++11)
class-name ( class-name && ) = delete;  (3) (since C++11)

class-name & class-name :: operator= ( class-name && )              (1) (since C++11)
class-name & class-name :: operator= ( class-name && ) = default;   (2) (since C++11)
class-name & class-name :: operator= ( class-name && ) = delete;    (3) (since C++11)
```

以下为 Move 类实现移动构造函数：

```cpp
// C++ program with declaring the move constructor
#include <iostream>
#include <vector>
using namespace std;
 
class Move {
private:
    int* data;

public:
    Move(int d)
    {
        // Declare object in the heap
        data = new int;
        *data = d;
        cout << "Common Constructor is called: " << d << endl;
    };
 
    // Copy Constructor
    // Move(const Move& source) = delete;
    Move(const Move& source): Move{ *source.data }
    {
        // Copying the data by making deep copy
        cout << "Copy Constructor (Deep copy):" << *source.data << endl;
    }
 
    // Move Constructor
    Move(Move&& source) : data{ source.data }
    {
        cout << "Move Constructor (No copy just move it):" << *source.data << endl;
        source.data = nullptr;
    }

    ~Move()
    {
        if (data != nullptr)
            cout << "Destructor is called for " << *data << endl;
        else
            cout << "Destructor is called for nullptr " << endl;

        // Free up the memory assigned to the data member of the object
        delete data;
    }
};
 
int main()
{
    vector<Move> vec;
    // cout << "capacity: " << vec.capacity() <<  endl;
    vec.push_back(Move{ 10 });
    vec.push_back(Move{ 20 });
    return 0;
}
```

可以注解掉移动构造函数对比运行结果，在移动构造函数的作用下，确实会减少不必要的开销。

有 Move Constructor 的运行输出结果如下：

    Common Constructor is called: 10
    Move Constructor (No copy just move it):10
    Destructor is called for nullptr
    Common Constructor is called: 20
    Move Constructor (No copy just move it):20
    Common Constructor is called: 10
    Copy Constructor (Deep copy):10
    Destructor is called for 10
    Destructor is called for nullptr
    Destructor is called for 10
    Destructor is called for 20

首先是 Move{ 10 } 执行普通构造器产生实例，接着移动语义生效，相应的实例被移动到 vector 向量容器中，所以解构函数只操作了一个 nullptr，并没有实际上释放内存。

接着 Move{ 20 } 执行普通构造过程，同样移动语义生效，接着实例被移动到 vector 向量容器中。

但是此时，容器空间不足，需要扩容，所以容器原有内容会被复制到新的内存空间。这就是为何出现了另一条构造 Move{ 10 } 的消息，并执行了拷贝构造函数，最终容器原内容被清理，也就是第一次真正的解构 Move{ 10 } 实例。

C++ STL 的 vector 容器在扩容时不会调用元素的移动构造函数，所以后续的扩容动作依然不够有效率。

要实现移动语义，必须让编译器知道什么时候需要复制，什么时候不需要复制，这就是右值引用发挥最大作用的地方。

为了让容器在扩容时不进行复制，这就是需要使用到 C++11 引入的 `=delete` 默认构造器删除说明符来禁止拷贝函数的使用，还有另一个新功能是显式标记默认构造函数 `=default`。

在定义了 Move Constructor 的前提下，直接注解 Copy Constructor 也可以。



## ⚡ auto_ptr to unique_ptr
- Dynamic memory management - Smart pointers https://en.cppreference.com/w/cpp/memory
- gcc libstdc++ auto_ptr.h https://gcc.gnu.org/onlinedocs/gcc-4.6.2/libstdc++/api/a00761_source.html

提示：新的 Rust 语言中，资源的所有权受到全面的管理，在指针的智能管理上是非常优秀的。

1998 年修订的第一版 C++ 标准只提供了一种智能指针： `std::auto_ptr`。 它基本上就像是个普通的指针： 通过地址来访问一个动态分配的对象。 std::auto_ptr 之所以被看作是智能指针，是因为它会在析构的时候调用 delete 操作符来自动释放所包含的对象。

当然这要求在初始化的时候，传给它一个由 new 操作符返回的对象的地址。 既然 std::auto_ptr 的析构函数会调用 delete 操作符，它所包含的对象的内存会确保释放掉。 

C++98 引入的智能指针 auto_ptr，对于拷贝构造和赋值运算符重载，该智能指针采用管理权转移的方式。当一个指针拷贝构造另一个指针时，当前指针就将对空间的管理权交给拷贝的那个指针，当前指针就指向空。

这种方式不符合指针的要求，可以允许多个指针指向同一块空间，将一个指针赋值给另一个指针的时候，就是需要让两个指针指向同一块空间。而 auto_ptr 只允许一块空间上只能有一个指针指向它，并且当管理权转移之后要想再访问之前的指针，就会出错，因为之前的指针已经为 NULL，就会出现解引用空指针的问题。

当和异常联系起来时这就更加重要了：没有 std::auto_ptr 这样的智能指针，每一个动态分配内存的函数都需要捕捉所有可能的异常，以确保在异常传递给函数的调用者之前将内存释放掉。

注意，auto_ptr 在 C++11 中已经被 unique_ptr 替代，C++11 引入移动语义 std::move，提出了 std::unique_ptr，才真正地完成了 std::auto_ptr 的设计意图，而原本的 std::auto_ptr 也被标记为 deprecated。

但是，由于以下原因，在 C++11 以后的版本中不推荐使用 auto_ptr，并会在 C++17 移除：

- ● auto_ptr 对象不能存储在 STL 容器中。
- ● auto_ptr 拷贝构造函数将从原始源中删除所有权，即原 auto_ptr 将失效。
- ● auto_ptr 拷贝赋值运算符会从原始源中删除所有权，即原 auto_ptr 将失效。
- ● auto_ptr 赋值运算符会删除右侧源对象的所有权，并将所有权分配给左侧对象，违反其原始意图。


C++11 借鉴了 boost 库里面的智能指针 `<memory>` 头文件定义：

- C++11 unique_ptr 就是 boost scoped_ptr；
- C++11 shared_ptr 就是 boost shared_ptr。


智能指针可以分为不同类型，以下是 C++11 的 memory 模块引入的几种基本类型：

- 独占型：std::unique_ptr，一份资源仅能由一个 std::unique_ptr 对象管理。
- 共享型：std::shared_ptr，一份资源可以由多个 std::shared_ptr 对象共同管理。当没有 std::shared_ptr 对象指向这份的资源，资源才会被释放，基于引用技术原理。
- 弱引用：std::weak_ptr，共享资源的观察者，需要和 std::shared_ptr 一起使用，不影响资源的生命周期。

智能指针不支持指针的算术运算，但是，智能指针通过运算符重载支持常用 * 和 -> 指针运算符。

不能使用其他 unique_ptr 对象的值来初始化一个 unique_ptr。同样，也不能将一个 unique_ptr 对象赋值给另外一个。这是因为，这样的操作将导致两个独占指针共享相同对象的所有权。但是可以通过 std::move() 将对象的所有权从一个独占指针转移到另外一个独占指针。

由于 std::unique_ptr 对象管理的资源，不可共享，只能在 std::unique_ptr 对象之间转移，因此 std::unique_ptr 就禁止了复制构造函数、赋值表达式，仅实现了移动构造函数。

简单说，使用 std::unique_ptr 对其独占所有权的资源进行管理，在离开 unique_ptr 对象的作用域时，会自动释放资源，这是很基本的 RAII 思想。

有趣的是，可以从函数中返回一个独占指针，在遇到函数返回 unique_ptr 对象时，编译器会自动应用 move() 操作以返回其值。

要销毁独占智能指针管理的任何可能存在的对象，只需要调用 reset()。

```cpp
template< class T, class Deleter = std::default_delete<T> > class unique_ptr;
template < class T, class Deleter > class unique_ptr<T[], Deleter>;
```

std::unique_ptr 有两个版本：

- 管理单个对象（例如以 new 分配的对象）
- 管理动态分配的对象数组（例如以 new[] 分配的对象）

说回已经被遗弃的 std::auto_ptr，以下代码演示其最大弊端，就是不能通过编译检测发现 auto_ptr 删除所有权问题：

```cpp
#include <new>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Shape;

typedef auto_ptr<Shape>  ShapePtr;
typedef unique_ptr<Shape>  UniShapePtr;

class Shape 
{
public:
  Shape(){ }
  Shape(string name): name(name){ }
  string name = "Basic Shape";
  friend ostream& operator<< (ostream& ost, const ShapePtr shapePtr);
};

ostream& operator<< (ostream& ost, const ShapePtr shapePtr)
{
  ost << "Shape: " << shapePtr->name << endl;
  return ost;
}

ostream& operator<< (ostream& ost, const UniShapePtr shapePtr)
{
  ost << "Shape: " << shapePtr->name << endl;
  return ost;
}

int main()
{
  ShapePtr shape(new Shape("Box"));
  ShapePtr another = shape; // Move to another
  // UniShapePtr another = move(shape); // Move to another
  cout << another;
  cout << shape;            // Violate access!
  cout << ShapePtr(new Shape());
}
```

以上代码中，shape 智能指针会将所有权转交 another，执行 auto_ptr 拷贝构造函数再释放对托管对象的所有权。但是后续代码还可以继续使用 shape，编译器并不给错误提示，但是运行程序时就崩。如果使用新的 unique_ptr 替代它，在转移所有权时，编译就会明确给出错误提示。

auto_prt 采用"Copy"语义，期望实现"Move"语义的实现有以下三大问题：

- auto_ptr 采用拷贝构造和拷贝赋值构造去实现"Move"语义，若将 auto_ptr 用值传递作为函数的参数，当函数执行结束时会导致资源被释放；
- auto_ptr 总是使用"non-array delete"，所以它不能用于管理 array 类的动态内存；
- auto_ptr 不能和 STL 容器和算法配合工作，因为 STL 中的"Copy"真的是"Copy"，而不是"Move"。

unique_ptr 示范：

```cpp
#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
 
struct B {
  virtual void bar() { std::cout << "B::bar\n"; }
  virtual ~B() = default;
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};
 
// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
int main()
{
  std::cout << "unique ownership semantics demo\n";
  {
      auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
      auto q = pass_through(std::move(p)); 
      assert(!p); // now p owns nothing and holds a null pointer
      q->bar();   // and q owns the D object
  } // ~D called here
 
  std::cout << "Runtime polymorphism demo\n";
  {
    std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
                                                  // as a pointer to base
    p->bar(); // virtual dispatch
 
    std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
    v.push_back(std::make_unique<D>());
    v.push_back(std::move(p));
    v.emplace_back(new D);
    for(auto& p: v) p->bar(); // virtual dispatch
  } // ~D called 3 times
 
  std::cout << "Custom deleter demo\n";
  std::ofstream("demo.txt") << 'x'; // prepare the file to read
  {
      std::unique_ptr<std::FILE, decltype(&std::fclose)> 
          fp(std::fopen("demo.txt", "r"), &std::fclose);
      if(fp) // fopen could have failed; in which case fp holds a null pointer
        std::cout << (char)std::fgetc(fp.get()) << '\n';
  } // fclose() called here, but only if FILE* is not a null pointer
    // (that is, if fopen succeeded)
 
  std::cout << "Custom lambda-expression deleter demo\n";
  {
    std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });  // p owns D
    p->bar();
  } // the lambda above is called and D is destroyed
 
  std::cout << "Array form of unique_ptr demo\n";
  {
      std::unique_ptr<D[]> p{new D[3]};
  } // calls ~D 3 times
}
```


## ⚡ shared_ptr & weak_ptr 共享智能指针
- https://en.cppreference.com/w/cpp/memory/weak_ptr
- https://en.cppreference.com/w/cpp/memory/shared_ptr
- 现代 C++：一文读懂智能指针 https://zhuanlan.zhihu.com/p/150555165

std::shared_ptr 其实就是对资源做引用计数——当引用计数为 0 的时候，自动释放资源。

共享指针方法参考：

- get() 函数返回存储的指针；
- use_count() 返回引用同一个托管对象的共享指针数量，即引用计数；
- swap() 交换两个共享指针的托管对象；
- reset() 释放当前共享指针拥有对象的所有权；
- std::weak_ptr<T>::lock() 将弱共享指针提供为共享指针；

std::weak_ptr 要与 std::shared_ptr 一起使用，可以将 weak_ptr 看做是 shared_ptr 对象管理的资源的观察者，它不影响共享资源的生命周期。如果需要使用 weak_ptr 正在观察的资源，通过 lock() 方法将 weak_ptr 提升为 shared_ptr。

当 shared_ptr 管理的资源被释放时，weak_ptr 会自动变成 nullptr。

```cpp
#include <iostream>
#include <memory>
 
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "gw.use_count() == " << gw.use_count() << "; ";
    // we have to make a copy of shared pointer before usage:
    if (std::shared_ptr<int> spt = gw.lock()) {
        std::cout << "*spt == " << *spt << '\n';
    }
    else {
        std::cout << "gw is expired\n";
    }
}
 
int main()
{
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;
 
        observe();
    }
 
    observe();
}
// Output:
// gw.use_count() == 1; *spt == 42
// gw.use_count() == 0; gw is expired
```

共享指针示范：

```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
 
struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the
                                  // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
 
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
}
```

Possible output:

    Base::Base()
      Derived::Derived()
    Created a shared Derived (as a pointer to Base)
      p.get() = 0x2299b30, p.use_count() = 1
    Shared ownership between 3 threads and released
    ownership from main:
      p.get() = 0, p.use_count() = 0
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 5
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 3
    local pointer in a thread:
      lp.get() = 0x2299b30, lp.use_count() = 2
      Derived::~Derived()
      Base::~Base()
    All threads completed, the last one deleted Derived

