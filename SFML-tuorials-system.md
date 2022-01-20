## ⚡ System Module

### 🗝 Time & Clock

和大多数库使用 uint32 来表达 milliseconds 或 flaot 来表达秒时间不同，SFML 使用弹性的类作为时间单位 *sf::Time*，它代表一个时间周期，即两个事件的之间的时间间隔。

sf::Time 不是 Datetime 不用来表达 year/month/day/hour/minute/second 这样的时间戳。它只是一个表示一定时间的值，如何解释它取决于使用它的上下文。

sf::Time 和秒、毫秒、微秒可以互相转化：

```cpp
sf::Time t1 = sf::microseconds(10000);
sf::Time t2 = sf::milliseconds(10);
sf::Time t3 = sf::seconds(0.01f);

sf::Time time = ...;

sf::Int64 usec = time.asMicroseconds();
sf::Int32 msec = time.asMilliseconds();
float     sec  = time.asSeconds();
```

sf::Time 可以进行算术运算：

```cpp
sf::Time t1 = ...;
sf::Time t2 = t1 * 2;
sf::Time t3 = t1 + t2;
sf::Time t4 = -t3;

bool b1 = (t1 == t2);
bool b2 = (t3 > t4);
```

SFML 提供 *sf::Clock* 实现所有程序基本都需要的时间计量功能，它只有两个函数：

- Time *getElapsedTime()* 返回计时器启动后的时间；
- Time *restart()* 重启计时器；

请注意，restart 会返回最后经过的时间，可以用它来替代 getElapsedTime 返回的旧值以避免出现微小的间隔。

```cpp
sf::Clock clock; // starts the clock
// ...
sf::Time elapsed1 = clock.getElapsedTime();
std::cout << elapsed1.asSeconds() << std::endl;
clock.restart();
// ...
sf::Time elapsed2 = clock.getElapsedTime();
std::cout << elapsed2.asSeconds() << std::endl;
```

在游戏循环逻辑中使用时间流逝值：

```cpp
sf::Clock clock;
while (window.isOpen())
{
    sf::Time elapsed = clock.restart();
    updateGame(elapsed);
    ...
}
```

### 🗝 Threads 线程
- classes for threading  http://en.cppreference.com/w/cpp/thread

线程就是 CPU 执行代码工作的一条流水线，通常每个程序至少有一个主线程来执行 main() 函数，主线程中可以再创建多个子线程。多线程的程序就可以同时利用 CPU 执行多个工作，可以理解为多车道的高速路，可以同时多车通过。

操作系统有线程的调度机制，会给不同的线程安排一个运行时间，所以多线程要处理同一数据时需要考虑线程同步问题，否则就不是线程安全的程序 NTS - not thread-safe。

SFML threads or std::thread?

新的 C++ 2011 规范中，引入了 std::thread 线程库，在此之前 SFML 已经实现了自己的线程库，到 SFML 2.0 发行的时候也没有多少编译器支持这个新标准。

现在新的编译器基本都支持 C++11，如果编译支持，那么就直接使用标准线程库，而不是 SFML 的私有版本。

说够了，来看看 SFML 多线程的代码示范，只创建一个额外线程：

```cpp
#include <SFML/System.hpp>
#include <iostream>

void func()
{
    // this function is started when thread.launch() is called

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread number one" << std::endl;
}

int main()
{
    // create a thread with func() as entry point
    sf::Thread thread(&func);

    // run it
    thread.launch();

    // the main thread continues to run...

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm the main thread" << std::endl;

    return 0;
}
```

主线程会因为子线程的调度延时而先执行信息打印，但那个线程先执行完 for 循环就不确定了。

如果 func 是类实例成员方法，那么线程就需要通过实例来调用：

```cpp
MyClass object;
sf::Thread thread(&MyClass::func, &object);
```

SFML 线程包装有三种方式，但是只有一种可以给待执行的函数传入一个泛型参数：

```cpp
template<typename F >  
  Thread (F function)  
  
template<typename F , typename A >  
  Thread (F function, A argument)  
  
template<typename C >  
  Thread (void(C::*function)(), C *object)  
  
  ~Thread () 

void  launch () 
void  wait () 
void  terminate ()  
```

调用 launch() 使用线程执行后，可以使用 terminate() 来强制终结。主线程调用 wait() 可以让主线程进入阻塞状态，等待子线程执行完成再返回。子线程可以使用 sf::sleep() 暂停执行，将 CPU 时间让出来。

一个容易被忽视的问题是线程实例的有效执行，以下代码中 startThread 函数退出后，局部变量 thread 保存的线程实例也被清理了，所以不会执行：

```cpp
void startThread()
{
    sf::Thread thread(&funcToRunInThread);
    thread.launch();
}

int main()
{
    startThread();
    // ...
    return 0;
}
```

# to be continue ...