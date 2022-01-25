# 🚩 C++: Big forest
- [初识 Rust](https://wudaijun.com/2020/02/rust-basic/)
- [Cppreference Archives](https://en.cppreference.com/w/Cppreference:Archives)
- [C++ Quick Guide](https://www.tutorialspoint.com/cplusplus/cpp_quick_guide.htm)
- [Visual Studio 2019 C++ 语言文档](https://docs.microsoft.com/zh-cn/cpp/cpp/)
- [欢迎回到新式 C++](https://docs.microsoft.com/zh-cn/cpp/cpp/welcome-back-to-cpp-modern-cpp)
- C++11 - the new ISO C++ standard https://www.stroustrup.com/C++11FAQ.html
- C++17 features, Tony Tables https://github.com/tvaneerd/cpp17_in_TTs/blob/main/ALL_IN_ONE.md
- 重读 The C Programming Language https://zhuanlan.zhihu.com/p/379408556
- Writing Compilers and Interpreters: A Modern Software Engineering Approach Using Java

面向对象编程的四大特征：

✔ `抽象` Abstraction 类与对象体现了 C++ 的抽象特征，即类是对象的抽象，对象是类的具体表现形式。
✔ `封装` Encapsulation 封装意味着对象只向外部世界提供有限的接口，隐藏对象的内部状态和实现细节。类与对象的数据成员、函数成员，以及数据成员和函数成员的公用、私有和保护特性体现了 C++ 的封装特性，无法从外部直接修改。封装简化了类的使用，因为用户只需要了解类的有限接口，而不需要了解类的内部实现细节，这可能很复杂。同时，程序员在编写类时总是可以通过封装来保持类实体的一致性。
✔ `继承` Reuse 重用类的继承与派生体现了 C++ 的继承特性。
✔ `多态` Polymorphism 类的虚函数体现了 C++ 的多态性。

面向对象概念创者 Alan Kay 强调消息 messaging 这一概念在 OOP 中所起的作用，即两个对象的消息通信是通过方法调用这一行为来实现。

The five SOLID principles are these:

• (SRP) Single responsibility principle — a class should have one, and only one, reason to change.
• (OCP) Open–closed principle — it should be possible to extend the behavior of a class without modifying it.
• (LSP) Liskov substitution principle — subclasses should be substitutable for their superclasses.
• (ISP) Interface segregation principle — many small, client-specific interfaces are better than one general-purpose interface.
• (DIP) Dependency inversion principle — depends on abstractions, not concretions.

推荐书单之前，先掌握技术书阅读方法论：

- 略读、泛读，速读一遍，最好在 1 ~ 2 天内完成，甚至是几个小时，主要目的是提取内容关键字；
- 精读一遍，在 2 周内看完，需要在时间充分的条件下进行；
- 深入实践，在整个过程中都要结合实践，也就是配合阅读做实验加深理解，并发现理解误区；
- 当你不精读后并结合实践还不能理解，请果断放弃并更换其它选择，目前此书不适合你阅读，即使好书你也吸收不了。

人的大脑记忆力有限，并且有遗忘时间曲线。在一天内快速看完一本书会在大脑里留下深刻印象，对于之后复习以及总结都会有特别好的作用。

但是，这种短时记忆是牢固，在一定时间内不进行重复加固，就会被大脑遗弃，因为它觉得这对你来说不是重要的事。

对于每一章的知识，先阅读标题，弄懂大概讲的是什么主题，再去快速看一遍。不懂也没有关系，但是一定要在不懂的地方做个记号，什么记号无所谓，但是要让自己后面再看的时候有个提醒的作用，看看第二次看有没有懂了些。

有了前面速读的感觉，第二次看会有慢慢深刻了思想和意识的作用，大脑就是这种工作模式。现在人类可能还没有总结出为什么大脑对记忆的完全方法论，但是，就像我们专业程序员，打代码都是先实践，然后就渐渐懂了过程，慢慢懂了原理。

记住一句话：每看完一个章节后，总结一下这个章节讲了啥，这是吸收记忆并释放记忆力的关键。

以下是 C/C++ 语言入门及深入的书单，StackOverflow 上也有 The Definitive C++ Book Guide and List 和 The Definitive C Book Guide and List。

注意 C/C++ 语言并不等于计算机科学，需要结构其它更细分领域的知识才通知用好，包括数据结构与算法，计算机网络编程等等，操作系统原理，编译原理，这很重要！还有计算机硬件体系结构，以及各种软件工具，如 GNC GCC 编译器和 GDB 调试工具等等。

C++ 是一门很难掌握的语言，极其灵活且强大，体系庞大，支持各种编程范式：

- 面向过程（Procedure Programming, PP）
- 面向对象（Object Oriented Programming, OOP）
- 泛型编程（Generic Programming，GP）
- 函数编程（Lambda 表达式实现）

作为专业人员，我想说个笑话：C++ 未入门！

推荐使用配套工具，可以跨平台可使用：

- CMake + Ninja 自动化工程编译脚本生成器；
- GNU GCC 编译器套件，Windows 系统下使用 MinGW 移植版；
- Git + Github 作为代码版本管理以及笔记同步管理工具； 
- Visual Studio Code 或 Sublime Text 作为文字处理及 IDE 开发工具；

C/C++ 语言入门：

- C Primer Plus, 6th Edition By Stephen Prata
- C++ Primer Plus 6th By Stephen Prata
- Essential C++
- Accelerated C++
- C++ FAQs, Second Edition By Marshall Cline, Greg Lomow, Mike Girou
- The Design and Evolution of C++ By Bjarne Stroustrup

C/C++语言进阶之路：

- Expert C Programming: Deep C Secrets By Peter van der Linden
- C Traps and Pitfalls By Andrew Koenig
- C Programming FAQs By Steve Summit (495个C语言问题)
- Pointers On C 1st Edition By Kenneth Reek
- Pointers On C: Instructors Guide By Kenneth Reek
- Pointers in C A Hands on Approach by Naveen Toppo, Hrishikesh Dewan
- The C programming Language 2nd By Brian W. Kernighan and Dennis M. Ritchie.
- The C++ Programming Language By Bjarne Stroustrup (4th ed updated for C++11)
- Thinking in C++ By Bruce Eckel, 2nd Edition Volume 1/2, 2000
- Effective C++ By Scott Meyers
- More effective C++ By Scott Meyers
- Exceptional C++: 47 engineering puzzles, programming problems, and solutions
- More Exceptional C++: 40 New Engineering Puzzles, Programming Problems, and Solutions
- The C++ standard library
- Effective STL
- Generic programming and the STL（泛型编程与STL）

- 紧跟时代更新：

- A Tour of C++ By Bjarne Stroustrup (2nd edition for C++17)
- Overview of the New C++ (C++11/14) By Scott Meyers

C++ 进阶：

- C++ Concurrency In Action By Anthony Williams
- Advanced C++ Programming Styles and Idioms By James Coplien
- Modern C++ Design: Generic Programming and Design Patterns Applied By Andrei Alexandrescu
- Inside the C++ Object Model By Stanley Lippman（经典古老系列深度探索C++对象模型）
- Design Patterns in Modern C++ Reusable Approaches for OO Software Design By Dmitri Nesteruk


C Primer 和 C Primer plus 这是目前市场上，最适合自学的 C 语言书籍。你可以在书中找到所有 C 语言编程概念的详细解释。这本书为每一个单独的概念提供了简短的例子，帮助读者更好理解。比如，指针这一章节就体现了这个特点。指针章节是本书编写最出色的章节之一。指针用来标识内存中的具体位置并且存放相应内存地址。书中参照了最新的ANSI标准C99。对于初级程序员来说，本书对学习基本概念大有帮助。这些概念在其他语言（比如：PHP和JAVA中）也有所应用。

《C专家编程》 你是准备进一步提高编程技巧的C语言专家吗？《C专家编程》就是为你准备的，它可以帮助程序员理解高级的C语言概念，强调程序员常用的一些最佳C语言技巧。这本书写得十分有趣，展现了作者在SUN系统（SUN SYSTEM）中的丰富经验。还定义了一些传统的编程方式，比如使用不同的声明方式。同时，还提供了很多实用的编程实践提示，比如，指针和数组之间的差别。

《C和指针》

本书通过对指针的基础知识和高级特性的探讨，帮助程序员把指针的强大功能融入到自己的程序中去。全书共18章，覆盖了数据、语句、操作符和表达式、指针、函数、数组、字符串、结构和联合等几乎所有重要的C编程话题。 适合C语言初学者和初级c程序员阅读，也可作为计算机专业学生学习C语言的参考。 　　

《你必须知道的495个C语言问题》

本书以问答的形式组织内容，讨论了学习或使用C语言的过程中经常遇到的一些问题。书中列出了C用户经常问的400多个经典问题，涵盖了初始化、数组、指针、字符串、内存分配、库函数、C预处理器等各个方面的主题，并分别给出了解答，而且结合代码示例阐明要点。

本书结构清晰，讲解透彻，是各高校相关专业C语言课程很好的教学参考书，也是各层次C程序员的优秀实践指南。

《Essential C++》 

这是一本内容不多但很实用的C++入门书籍，强调快速上手与理解C++编程。本书主要围绕一系列逐渐复杂的程序问题，以及用以解决这些问题的语言特性展开讲解。你不只学到C++的函数和结构，也会学习到它们的设计目的和基本原理。

《C++ Primer》

本书对C++基本概念、技术、以及现代C++编程风格进行了全面而且权威的阐述，是C++初学者的最佳指南；本书可以帮助你编写实用的程序，而无需首先精通每个语言细节。对于中高级程序员，本书也是不可或缺的参考书。

《Effective C++》和《More effective C++》

作者Scott Meyers。你应该熟读它们，并清楚地理解每个项目。该书围绕55条准则，每一条都介绍了一个可让你写出更好的C++程序代码的方法，并以特别设计过的例子详加讨论。

《Exceptional C++（C++编程剖析）》和《More exceptional C++》

这两本书中都包含了40个C++编程问题，这些问题会让你磨练自己的技能，最终成为优秀的C++程序员。这些问题是Herb Sutter精心挑选，与ISO/ANSI C++官方标准相一致，帮助程序员在设计、架构和编码过程中保持良好的风格，从而使编写的C++软件更健壮、更高效。

《The C++ standard library（C++标准程序库）》

这是标准模板库字典，你可以在本书中找到STL相关的一切知识。本书焦点放在标准模板库、检查容器、迭代器、函数对象和STL算法上。每一个元素都有深刻的呈现，包括其介绍、设计、运用实例、细节解说、陷阱、意想不到的危险，以及相关类别和函数等。

《Effective STL》

这是Scott Meyers的第三本C++专著，也是学习STL最权威的书籍。作者对书中的50个指导方针都作了详尽的分析，并配以示例。通过这些规则，C++开发者可以最大限度地使用STL。

《Generic programming and the STL（泛型编程与STL）》

本书阐述了泛型程序设计的核心理念：concepts（概念）、modeling（模型）和refinement（改善），并为你展示这些观念如何导出STL的基础概念：iterators（迭代器）、containers（容器）和function objects（函数对象）。按照本书所述，你可以把STL想象成一个由concepts组成的library，你将学习到STL正式结构并理解其强大的优势。

《Modern C++ design（现代C++设计）》

作者Andrei Alexandrescu为C++程序员打开了一个新的局面。本书提供了一些针对软件设计的前沿方法，如联合设计模式、泛型编程，使程序员可以编写有表现力的、灵活的、高度可重用的代码。

《Inside the C++ object model（深度探索C++对象模型）》

本书专注于C++面向对象程序设计的底层机制，包括结构式语意、临时性对象的生成、封装、继承，以及虚拟——虚拟函数和虚拟继承，帮助你理解程序的底层实现，以便写出更高效的代码。

