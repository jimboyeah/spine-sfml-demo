
# 🚩 SFML Framework 入门教程

Windows 系统安装 SFML 可以直接下载预编译文件，也可以下载源代码编译生成。

Linux 系统安装 SFML 有多种方法，最好的方法是使用分发包仓库安装：

    sudo apt-get install libsfml-dev

其次是编译源代码再安装，或者下载预编译文件再手动解压拷贝到 /home/me/sfml 或 /usr/local 这些标准目录下，官方网站提供 GCC - 64-bit 预编译文件下载。

如果安装在非标准目录，可以将路径导出：

    export LD_LIBRARY_PATH=<sfml-install-path>/lib && ./sfml-app

使用命令编译、链接程序，非标准安装目录需要手动指定 SFML 安装路径：

    g++ -c main.cpp
    g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

    g++ -c main.cpp -I<sfml-install-path>/include
    g++ main.o -o sfml-app -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system

如果要编译源代码，SFML 已经在源代码压缩包中为 Windows & macOS 系统提供了依赖的头文件和链接库，不需要额外下载。

但在 Linux 系统上，需要为了编译 SFML 源代码安装所有依赖库：

- freetype
- x11
- xrandr
- udev
- opengl
- flac
- ogg
- vorbis
- vorbisenc
- vorbisfile
- openal
- pthread


macOS 系统下安装 SFML 系统要求：

- A 64-bit Intel Mac with Lion or later (10.7+)
- Xcode (versions 4 or above of the IDE, which is available on the App Store, are supported).
- Clang and libc++ (which are shipped by default with Xcode).

SFML 在 macOS 系统上有两种二进制格式，dylib vs framework，推荐使用后者。Dylib 就是动态链接库，和 Linux 的 .so 库文件类似。Frameworks 格式也类似 dylibs，除了可以封装外部资源。需要注意的细微区别是，如果您自己构建 SFML，那么可以在发布和调试配置中获得动态库。但是，Frameworks 仅在发行版本配置中可用。在任何一种情况下，这都不应该成为问题，因为在发布应用程序时都应该使用 SFML 的发布版本。这就是为什么官方网站下载页面上提供的 OS X 二进制文件只在发行配置中有效。

下载 SFML SDK 后，Clang - 64-bit (OS X 10.7+, compatible with C++11 and libc++) ，处理以下三部分内容：

- Header files and libraries
    - 拷贝 Frameworks 文件到 /Library/Frameworks。
    - 拷贝 lib 内的动态库到 /usr/local/lib，以及 include 内的头文件到 /usr/local/include。
- SFML 在 macOS 系统的依赖库，拷贝 extlibs 到 /Library/Frameworks。
- Xcode templates 推荐安装这部分可选的工和模板。拷贝模板中的 SFML 目录到 ~/Library/Developer/Xcode/Templates。


## ⚡ Module Dependencies

SFML 是模块化的框架：

- System 系统底层的处理模块，如时间、线程、用户数据流，包括手柄 API 的适配，工具类的实现；
- Graphics 图形处理模块，如字体图形处理使用了 freetype，还有 OpenGL 图形接口；
- Window 图形窗口适配，主要是用户界面的交互；
- Audio 音频处理模块，支持多种格式的音频；
- Network 网络通信模块，如联机游戏支持，FTP 应用等；

各个模块在不同的系统下有不同的依赖关系。

Windows 平台下的依赖关系，文件名中的 -s 后缀表示静态链接库，-d 表示带调试符号，不带这些后缀的用于动态链接库：

- System (sfml-system-s.lib)
    - winmm.lib
- Graphics (sfml-graphics-s.lib)
    - sfml-window-s.lib
    - sfml-system-s.lib
    - opengl32.lib
    - freetype.lib
- Window (sfml-window-s.lib)
    - sfml-system-s.lib
    - opengl32.lib
    - winmm.lib
    - gdi32.lib
- Audio (sfml-audio-s.lib)
    - sfml-system-s.lib
    - openal32.lib
    - flac.lib
    - vorbisenc.lib
    - vorbisfile.lib
    - vorbis.lib
    - ogg.lib
- Network (sfml-network-s.lib)
    - sfml-system-s.lib
    - ws2_32.lib


