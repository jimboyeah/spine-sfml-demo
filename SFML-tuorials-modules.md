
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
- Graphics 模块基于 OpenGL 提供图形处理能力，还有如字体图形处理使用了 freetype；
- Window 操作系统图形窗口适配，主要是用户界面的交互；
- Audio 音频流处理模块，支持多种格式的音频，录音，空间化 spatialization；
- Network 网络通信模块，如联机游戏支持，HTTP、FTP 等应用等；

SFML 本身是基于 OpenGL 接口规范构建的，但其本身只是做了与操作的适配工作，以实现框架的跨平台的适用性。OpenGL 接口规范定义的 API 在 SFML 的源代码中 \SFML\Graphics\GLLoader.hpp，这相当一个 GLUT 或者 GLFW 这样的 API 导入工具。头文件定义了 OpenGL 的常量、标准 API 和扩展 API。

SFML 完成编译后不会再使用这个头文件，所以在预计编译的下载包中并没有包含这个 OpenGL API 加载器。

各个模块在不同的系统下有不同的依赖关系。

Windows 平台下的依赖关系，文件名中的 -s 后缀表示静态链接库，-d 表示带调试符号，不带这些后缀的用于动态链接库：

- System (sfml-system-s.lib `#include <SFML/System.hpp>`)
    - winmm.lib
- Graphics (sfml-graphics-s.lib `#include <SFML/Graphics.hpp>`)
    - sfml-window-s.lib
    - sfml-system-s.lib
    - opengl32.lib
    - freetype.lib
- Window (sfml-window-s.lib `#include <SFML/Window.hpp>`)
    - sfml-system-s.lib
    - opengl32.lib
    - winmm.lib
    - gdi32.lib
- Audio (sfml-audio-s.lib `#include <SFML/Audio.hpp>`)
    - sfml-system-s.lib
    - openal32.lib
    - flac.lib
    - vorbisenc.lib
    - vorbisfile.lib
    - vorbis.lib
    - ogg.lib
- Network (sfml-network-s.lib `#include <SFML/Network.hpp>`)
    - sfml-system-s.lib
    - ws2_32.lib

官方文档提供了一个简短的例子来帮助大概了解 SFML 框架：

```cpp
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cute_image.jpg"))return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to displaysf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Hello SFML", font, 50);

    // Load a music to playsf::Music music;
    if (!music.openFromFile("nice_music.ogg")) 
        return EXIT_FAILURE;

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed) window.close();
        }
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
```

注意，在 Windows 系统创建项目时，程序的入口可能被设置为专用的 WinMain，而不是标准的 C/C++ 主函数 main，这样就不能在 Linux 或 macOS 中使用。SFML 提供了一个 main 模块来做入口适配工作，这大概是最简单的一个模块了，文档上也没过多说明。使用它，只需要引用 sfml-main-d.lib 或 sfml-main.lib，分别对应 Debug 和 Release 两种配置。

使用 Code::Blocks (MinGW) 做开发时，文档建议不要使用其内置的 SFML 工程模板，因为更新不及时，可能不兼容最新的 SFML。

因为链接方式使用了 */SUBSYSTEM:CONSOLE*，很多程序运行时会自带一个控制台，即使是有图形界面。因为 Windows 控制台程序和图形界面不冲突，可以在同一个程序同时使用。

而完全使用图形界面，隐藏控制台，即不使用控制台子系统，就意味着程序需要提供 *WinMain* 作为入口。并且失去 C/C++ 程序通过标准输入输出功能，无法使用控制台打印消息，也无法获取控制台输入。但是，程序为了保证兼容，还是会保留 *main*，并且通过 *WinMain* 来调用标准的 C/C++ 程序入口。

```cpp
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    return main(__argc, __argv);
}
```

在 CMake 中可以通过以下方式设置链接选项来确定子系统：

```sh
set(CMAKE_EXE_LINKER_FLAGS "/subsystem:windows")
add_link_options("/subsystem:windows")
target_link_options(some_exe PUBLIC "/subsystem:windows")
```

这三种方式的差别在于：

- 通过 *set* 命令设置的链接标志可能会被其它命令设置的标记覆盖；
- 通过 *add_link_option* 命令设置的链接参数会被所有目标使用；
- 通过 *target_link_options* 设置的链接参数只对指定的目标有效。
