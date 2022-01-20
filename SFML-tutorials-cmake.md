# 🚩 SFML CMake 项目配置入门
- [SDL - Simple DirectMedia Layer](https://www.libsdl.org/)
- [Lazy Foo's SDL Tutorials](https://tjumyk.github.io/sdl-tutorial-cn/contents.html)
- [SFML - Simple and Fast Multimedia](https://github.com/SFML/sfml)
- [Tutorials for SFML 2.5](https://www.sfml-dev.org/tutorials/2.5/)
- Spine Examples https://github.com/EsotericSoftware/spine-runtimes/tree/4.0/examples
- Spine User Guide http://esotericsoftware.com/spine-user-guide
- Rhubarb Lip Sync for Spine https://github.com/DanielSWolf/rhubarb-lip-sync

SDL 和 SFML 作为轻量级图形框架，常用用于 GUI 程序及游戏开发，就开发者活跃度来看，基于 C++ 的 SFML 占优势，像 Spine 动画制作软件都提供提供了运行时支持，大大方便了游戏制作流程。这些框架做了不同系统平台的图形接口的适配工作，使用者就不再需要基于操作系统底层 API 来开发图形应用程序，开发者就可以不深入 Windows 系统下的 DirectX，Linux 系统下的 X Window System，Mac OS 使用通用的 OpenGL 图形接口的细节。

Spine 运行时提供了示范 Spine-SFML 示范工程，可以克隆下载：

>git clone git@github.com:EsotericSoftware/spine-runtimes
>git clone -b 4.0 --single-branch git@github.com:EsotericSoftware/spine-runtimes

SFML 官方提供预编译文件下载，其中就包含 SFML-2.4.1\cmake\Modules\FindSFML.cmake，可以使用 CMake 脚本加载它来使用 SFML 框架。

SFML 作为跨平台的图形框架，可以在不同的平台工具中开发，根据需要下载预编译文件或源文件：

- SFML and Visual Studio
- SFML and Code::Blocks (MinGW)
- SFML and Linux
- SFML and Xcode (macOS)
- Compiling SFML with CMake

对于 Windows 平台，官方网站提供了 MSVC、GCC TDM、GCC MinGW 三套编译器的 32-bit 和 64-bit 预编译文件，根据自身使用的编译版本需要下载对应的预编译文件，下载页面也非常贴心地提供了相应 GCC TDM/MinGW 编译器的下载地址：

    Visual C++ 11 (2012) - 32-bit    Visual C++ 11 (2012) - 64-bit
    Visual C++ 12 (2013) - 32-bit    Visual C++ 12 (2013) - 64-bit
    Visual C++ 14 (2015) - 32-bit    Visual C++ 14 (2015) - 64-bit
    GCC 4.9.2 TDM (SJLJ) - 32-bit    GCC 4.9.2 TDM (SJLJ) - 64-bit
    GCC 6.1.0 MinGW (DW2) - 32-bit   GCC 6.1.0 MinGW (SEH) - 64-bit

要求编译版本 100% 一致，否则会出现找不到符号定义错误，自行编译源代码生成 SFML 库是一个方法。

而 CMake 作为一个强大的自动化工程编译脚本工具，是值得推荐使用的，有了 CMake 就可以替代各种 make 工具的脚本编写。

推荐的工具配置列表，它们可以完美配合，经量高效：

- Sublime Text 编码编写工具；
- CMake 自动化编译脚本生成工具；
- Ninja 自动化编译工具；
- Vcpkg C++ 依赖管理工具；

## ⚡ CMakeLists.txt Demo

为依赖 SFML 的客户工程编写编译脚本 CMakeLists.txt，根据安装位置在脚本中设置 FindSFML.cmake 查找脚本的位置，因为是非标准安装路径所以使用了 SFML_ROOT 变量：

    # CMakeLists.txt example:
    cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

    option(UseMSVC "Using MSVC Compiler" ON)
    if(UseMSVC)
        set(CMAKE_C_COMPILER cl.exe)
        set(CMAKE_CXX_COMPILER cl.exe)
        set(CMAKE_RC_COMPILER rc.exe)
        set(SFML_VER "SFML-2.4.1-vc14-64-bit")
    endif()

    project(SFML_Win32)

    option(MINGW "Using MinGW Library file name rule" OFF)
    IF(MINGW)
        SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
        SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")
        add_definitions(-D_WIN32)
        set(SFML_VER "SFML-2.4.1-mingw-gcc6.1-32-bit")
    ENDIF(MINGW)

    find_path(SFML_FRAMEWORK "${SFML_VER}" "../../dependencies/")
    if(SFML_FRAMEWORK)
        set(SFML_ROOT "${SFML_FRAMEWORK}/${SFML_VER}")
        message("SFML Framework Found: " ${SFML_ROOT})
    else()
        message("SFML Framework Not found: " ${SFML_VER})    
    endif()

    # set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")
    list(APPEND CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules/")
    list(APPEND CMAKE_PREFIX_PATH "${SFML_ROOT}/cmake/Modules/")

    set(SFML_STATIC_LIBRARIES TRUE)
    find_package(SFML COMPONENTS system window graphics audio network)
    include_directories(${SFML_INCLUDE_DIR})

    add_executable(sfml_window examples/window.cpp)
    target_link_libraries(sfml_window ${SFML_LIBRARIES} opengl32 winmm )
    target_link_libraries(sfml_window ${SFML_DEPENDENCIES} )

    foreach(item ${SFML_LIBRARIES})
        message("SFML_LIBRARIES:" ${item})
    endforeach()
    foreach(item ${SFML_DEPENDENCIES})
        message("SFML_DEPENDENCIES:" ${item})
    endforeach()

编写好 CMake 脚本后，就可以测试编译脚本的生成，以及执行编译工作：

    cmake -H. -B_builds -DCMAKE_VERBOSE_MAKEFILE=ON
    cmake --build _builds

根据客户程序使用的功能，比如，SFML 提供的示例使用了 OpenGL，就需要添加 OpenGL 库文件。如果使用静态链接，比如在 Windows 则还可能会需要 DirectX SDK。如果使用了摇杆设备 API 如 joyGetDevCapsW，可以添加 winmm.lib 依赖库，否则会有 LNK2019: 无法解析的外部符号错误。

使用 Graphics 模块时，静态编译还会需要 jpeg.lib 这些 SFML 依赖库，可以将 SFML_DEPENDENCIES 中的依赖库也链接到客户程序上。

除了使用 CMake 生成工程的编译脚本，还有 Ninja 也是值得推荐使用的构建系统。它的编译效率更高，还会自动在 CMakeLists.txt 文件更新后自动重新生成编译脚本，可以用来替代其它 make 工具。它只有一个可执行文件，和 CMake 搭配使用，真正小巧可爱。

```sh
$ start https://github.com/microsoft/vcpkg/releases
$ start https://github.com/ninja-build/ninja/releases
$ git clone git://github.com/ninja-build/ninja.git && cd ninja
$ git checkout release
$ cat README.md
```

以下使用生成器为 Ninja 生成编译脚本，CMake 会为 Ninja 脚本默认设置 GCC 编译器。可以在 CMake 脚本中指定要使用的编译器，可以看到以下检测结果中显示指定了 MSVC C++ 编译器。如果测试出现的错误，需要根据信息来解决问题。如果是找不到符号或库文件，通常有可能是库文件目录配置引起。

CMake 会通过编译一段测试程序对编译器进行 ABI 信息测试，期间可能会收到以下错误信息。所谓 ABI，是指应用程序二进制接口（Application Binary Interface, ABI）。

    >cmake -H. -S. -Bbuild -DCMAKE_VERBOSE_MAKEFILE=ON -G "Sublime Text 2 - Ninja"
    -- The C compiler identification is GNU 10.2.0
    -- The CXX compiler identification is MSVC 19.26.28806.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: C:/mingw/bin/cc.exe - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - failed
    -- Check for working CXX compiler: C:/MSVC2019/Community/VC/Tools/MSVC/14.26.28801/bin/Hostx64/x64/cl.exe
    -- Check for working CXX compiler: C:/MSVC2019/Community/VC/Tools/MSVC/14.26.28801/bin/Hostx64/x64/cl.exe - broken
    CMake Error at C:/CMake/share/cmake-3.18/Modules/CMakeTestCXXCompiler.cmake:59 (message):
      The C++ compiler

        "C:/MSVC2019/Community/VC/Tools/MSVC/14.26.28801/bin/Hostx64/x64/cl.exe"

      is not able to compile a simple test program.

      It fails with the following output:
      ...
        LINK : fatal error LNK1104: 无法打开文件“kernel32.lib”

执行脚本前，先执行 MSVC 环境配置批处理脚本，根据需要设置平台类型，如 x86 或 x64，然后再执行 CMake -G 生成构建脚本：

    > "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat" x86
    > cmake .. -G "Sublime Text 2 - Ninja"

虽然可以在 CMake 脚本中调用批处理文件，但是环境变量设置并不能返回供 CMake 后续使用：

    execute_process(COMMAND "vcvars64.bat" "x64")

这个问题可以在 Sublime 中解决，在执行编译工具前调用 MSVC 的环境配置脚本。

另外，Vcpkg 也是不错的一个依赖管理工具，开发 C/C++ 程序，少不了编译开源的第三方库。比如用于网络连接的高性能库 libcurl、用于压缩解压的 zlib 等等。使用这些库开发极大的方便了程序员，使得我们不必重复造轮子。由于这些开源库绝大部分都来源于 Linux 系统，其工程文件、编译系统都使用 gnu 系列工具，使得将其移植到 Windows 的 VC 开发环境下一直是难点。

还需要考虑预先编译出哪种类型的开源库程序，比如：Debug 还是 Release、动态库还是静态库、MD 还是 MT、32 位还是 64 位。光是这三种组合就有 16 种可能性。如果像 libcurl 这种还要考虑是否引用其他开源库的功能，那么编译类型的组合会更多。

VCpkg 就是解决这个问题的：

- 自动调用 git 等工具下载开源库源代码；
- 源码包的缓存管理和版本管理，可以升级版本；
- 紧密结合 CMake 轻松编译；
- 依赖关系检查，比如编译 libcurl，会自动下载 zlib、openssl 进行编译；
- 无缝集成 Visual Studio，不需要设置库文件、头文件的所在目录，自动集成。
- Visual Studio 全平台支持，支持 Debug/Release、x86/x64 编译，还支持 UWP、ARM 平台的编译。

下载 Vcpkg 源代码后，使用 PowerShell 执行 Vcpkg 工程目录下的 bootstrap-vcpkg.bat 就会对 toolsrc 目录中保存的 Vcpkg C++ 源代码和组件代码进行编译，并在同级目录下生成 vcpkg.exe 文件。


## ⚡ Sublime Project

CMake 可以和 Sublime 配合工作，执行以下命令就会为工程生成 .sublime-project 项目文件，还有搭配使用的 Ninja 编译脚本：

    cmake -H./src -B./build -G \"Sublime Text 2 - Ninja\"

实际使用时不会直接使用生成的 Sublime 项目文件，而是直接配置自己的项目文件：

为了方便执行命令，在工程配置文件中指定了命令行工作目录设置 `working_dir`，执行 CMake 生成脚本时，就会在此目录下保存。注意，如何不存在此目录，命令不会被执行，可以直接设置为工程目录 *${project_path}*。

使用 ``file_regex``获取错误输出，用 Perl 的正则表达式来捕获构建系统的错误输出，主要包括四部分内容，分别是：

- file name
- line number
- column number
- error message

Sublime Text 在匹配模式中使用分组的方式捕获信息。 file name 和 line number 域是必须的。

当错误信息被捕获时，你可以使用 F4 和 Shift+F4 在你的项目文件中跳转。被捕获的 错误信息 会显示在状态栏。

Sublime 的 Build Systems 是很强大很灵活的，将命令配置保存在 `.build-system` 文件中即可以调用，F7 或 Ctrl-B 执行上一次编译命令，或 Ctrl-Shift-B 调用。

sublime 工程文件配置参考 spine-sfml.sublime-project 如下：

```json
{
    "build_systems":
    [
        {
            "name": "🤍CMake Generate -> MinGW Makefiles",
            "working_dir": "${project_path}/build",
            "encoding": "gbk",
            "quiet": true,
            "shell_cmd": "cmake -H. -S../dependencies/SFML-2.4.1-vc14-64-bit -G \"MinGW Makefiles\"",
            "env":
            {
                "PATH": "c:/MinGW/bin/;%PATH%"
            },
            "file_regex": "^(.+)\\((\\d+)\\)(): ((?:fatal )?(?:error|warning|note) \\w+\\d\\d\\d\\d): (.*)$",
            "variants":
            [
                {
                    "shell_cmd": "make --version && g++ --version && make help",
                    "name": "Make help"
                },
                {
                    "name": "clean",
                    "shell_cmd": "make clean"
                },
                {
                    "name": "clear all",
                    "shell_cmd": "del * /s /q"
                },
                {
                    "name": "Make",
                    "shell_cmd": "make -j 10 all"
                },
                {
                    "name": "Make install",
                    "shell_cmd": "make install"
                },
                {
                    "name": "Make test",
                    "shell_cmd": "make -j 10 && make test"
                }
            ]
        },
        {
            "name": "💛CMake Generate -> Ninja (Windows)",
            "working_dir": "${project_path}/build",
            "encoding": "gbk",
            "quiet": true,
            "cmd": ["echo", "shell_cmd cause this command disabled!"],
            "shell_cmd": "%VCVARS64% x64 && cmake -H. -S../dependencies/SFML-2.4.1-vc14-64-bit -DCMAKE_VERBOSE_MAKEFILE=ON -G \"Sublime Text 2 - Ninja\"",
            "env":
            {
                "PATH": "c:/MinGW/bin/;%PATH%",
                "VCVARS64": "\"C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvars64.bat\"",
            },
            // for MSVC Compiler message process
            "file_regex": "^(.+)\\((\\d+)\\): ((?:fatal )?(?:error|warning|note) \\w+): (.*)$",
            // for GCC Compiler message process
            // "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
            "variants":
            [
                {
                    "name": "Ninja - all",
                    "shell_cmd": "%VCVARS64% x64 && ninja.exe -f build.ninja all && echo Done!"
                },
                {
                    "name": "Ninja - clean",
                    "shell_cmd": "ninja.exe -f build.ninja clean"
                },
                {
                    "name": "Ninja - rebuild_cache",
                    "shell_cmd": "ninja.exe -f build.ninja rebuild_cache"
                },
                {
                    "name": "Ninja - test",
                    "shell_cmd": "ninja.exe -f build.ninja test"
                },
                {
                    "name": "Ninja - edit_cache",
                    "shell_cmd": "ninja.exe -f build.ninja edit_cache"
                }
            ]
        },
    ],
    "folders":
    [
        {
            "binary_file_patterns": [ "*.nothing" ],
            "name": "☾ SFML Demo Project",
            "path": "."
        }
    ]
}
```

