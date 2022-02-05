# 🚩 Spine & SFML
- git clone git@github.com:jimboyeah/spine-sfml-demo.git

本代码仓库用于提供 Spine 动画制作及 SFML Framework 入门的学习材料。

Spine 是一个专业的 2D 动画制作软件，功能强大，许多游戏动画制作都是基于它实现的。

SFML - Simple and Fast Multimedia 是一个轻量的跨平台图形编程框架，可以结合 OpenGL 进行相对底层但不太需要了解操作系统底层图形能力的细节。

部分代码来自 [Spine runtimes](https://github.com/EsotericSoftware/spine-runtimes)，包括 C 和 CPP，还有 spine-c、spine-cpp 两个目录，它们是 Spine 的运行时实现源代码，和基于 SFML 实现动画示范。提供了 CMake 脚本，会自行下载 SFML-2.4.1 依赖库，但是依赖路径经过修改，使用了 VC14-64-bit 版本：

    set(DEPS_DIR "${PROJECT_SOURCE_DIR}/dependencies/")

编译需要使用的编译可以是通过以下软件获得：

- Microsoft Visual Studio 2019 Community
- GNU GCC TDM/MinGW-w64


# 🚩 SFML Framework 入门教程

## SFML CMake 项目配置

- ✔[SFML CMake 项目配置入门](./SFML-tutorials-cmake.md)
- ✔[CMakeLists.txt Demo](./SFML-tutorials-cmake.md#-cmakeliststxt-demo)
- ✔[Sublime Project](./SFML-tutorials-cmake.md#-sublime-project)

## SFML Framework 入门教程

- ✔[Module Dependencies](./SFML-tuorials-modules.md)
- ✔[System Module](./SFML-tuorials-system.md)
- ⚡[Window Module](./#-to-be-continue)
- ⚡[Graphics Module](./#-to-be-continue)
- ⚡[Audio Module](./#-to-be-continue)
- ⚡[Network Module](./#-to-be-continue)

## C++ 知识补充

- ✔[C++: Big forest 书单](/SFML-tuorials-Big-forest.md)
- ✔[C++ OOP 面向对象编程](./SFML-tuorials-cpp.md)

    - ✔[Inheritances 继承](./SFML-tuorials-cpp.md#-Inheritances-继承)
    - ✔[Friend & Access Control](./SFML-tuorials-cpp.md#-Friend--Access-Control)
    - ✔[Override vs. Overwrite](./SFML-tuorials-cpp.md#-Override-vs-Overwrite)
    - ✔[Scope & Name-Hiding](./SFML-tuorials-cpp.md#-Scope--Name-Hiding)
    - ✔[CRTP Static Polymorphism 静多态](./SFML-tuorials-cpp.md#-CRTP-Static-Polymorphism-静多态)
    - ✔[Virtual & Polymorphism 虚拟与多态机制](./SFML-tuorials-cpp.md#-Virtual--Polymorphism-虚拟与多态机制)
    - ✔[Virtual and Multiple Inheritance](./SFML-tuorials-cpp.md#-Virtual-and-Multiple-Inheritance)
    - ✔[Class Layout 类数据结构布局](./SFML-tuorials-cpp.md#-Class-Layout-类数据结构布局)

- ✔[C++ FAQs Virtual Functions](SFML-tuorials-cpp-faqs.md#-C++-FAQs-Virtual-Functions)

    - ✔[FAQ 8.05 virtual 虚函数重写版该抛异常还是 no-op 什么也不做？](SFML-tuorials-cpp-faqs.md#-FAQ-805-virtual-虚函数重写版该抛异常还是-no-op-什么也不做)
    - ✔[FAQ 19.10 为什么友元不能是 virtual？](SFML-tuorials-cpp-faqs.md#-FAQ-1910-为什么友元不能是-virtual)
    - ✔[FAQ 20.12 没有代码的 virtual 解构器如何定义?](SFML-tuorials-cpp-faqs.md#-FAQ-2012-没有代码的-virtual-解构器如何定义)
    - ✔[FAQ 20.13 基类构造器调用 virtual 函数时为何不是调用重写版本?](SFML-tuorials-cpp-faqs.md#-FAQ-2013-基类构造器调用-virtual-函数时为何不是调用重写版本)
    - ✔[FAQ 21.07 virtual 虚构造器是什么？](SFML-tuorials-cpp-faqs.md#-FAQ-2107-virtual-虚构造器是什么)

- ✔[Smart Pointers 智能指针](./SFML-tuorials-smart-pointer.md#-Smart-Pointers)

    - ✔[lvalue & rvalue reference 左值右值引用](./SFML-tuorials-smart-pointer.md#-lvalue--rvalue-reference)
    - ✔[Move Constructors 移动构造函数](./SFML-tuorials-smart-pointer.md#-Move-Constructors)
    - ✔[auto_ptr to unique_ptr 独占智能指针](./SFML-tuorials-smart-pointer.md#-auto_ptr-to-unique_ptr)
    - ✔[shared_ptr & weak_ptr 共享智能指针](./SFML-tuorials-smart-pointer.md#-shared_ptr--weak_ptr-共享智能指针)

