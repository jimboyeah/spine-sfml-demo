cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(UseMSVC "Using MSVC Compiler" ON)
if(UseMSVC)
    set(CMAKE_C_COMPILER cl.exe)
    set(CMAKE_CXX_COMPILER cl.exe)
    set(CMAKE_RC_COMPILER rc.exe)
    set(SFML_VER "SFML-2.4.1") # -vc14-64-bit
endif()

project(SFML_Win32 CXX)
cmake_policy(SET CMP0074 NEW)

option(MINGW "Using MinGW Library file name rule" OFF)
IF(MINGW)
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")
    add_definitions(-D_WIN32)
    set(SFML_VER "SFML-2.4.1-mingw-gcc6.1-32-bit")
ENDIF(MINGW)

# include_directories("c:/VulkanSDK/1.2.198.1/Include")
# include_directories("c:/VulkanSDK/1.2.198.1/Lib")


set(DEPS_DIR "${PROJECT_SOURCE_DIR}/dependencies/")
function(install_deps Directory FileName URL)
    set(DEP_DIR ${DEPS_DIR}/${Directory})
    if (NOT EXISTS "${DEP_DIR}")
        message("Try to download and install ${FileName}")
        if(NOT EXISTS ${DEPS_DIR}/${FileName})
            message("Downloading ${URL}")
            file(DOWNLOAD "${URL}" "${DEPS_DIR}/${FileName}")
        endif()
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar -xzf "${FileName}"
            WORKING_DIRECTORY ${DEPS_DIR}
        )
    endif()
endfunction()


# set(SFML_URL "http://www.sfml-dev.org/files/SFML-2.4.1-linux-gcc-64-bit.tar.gz")
set(SFML_URL "http://www.sfml-dev.org/files/SFML-2.4.1-windows-vc14-32-bit.zip")
install_deps("SFML-2.4.1" "SFML-2.4.1-windows-vc14-32-bit.zip" ${SFML_URL})

set(FreeGLUT_URL "http://prdownloads.sourceforge.net/freeglut/freeglut-3.2.2.tar.gz?download")
install_deps("freeglut-3.2.2" "freeglut-3.2.2.tar.gz" ${FreeGLUT_URL})

# set(GLFW_URL "https://github.com/glfw/glfw/archive/refs/tags/3.3.6.tar.gz")
set(GLFW_URL "https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.zip")
install_deps("glfw-3.3.6" "glfw-3.3.6.zip" ${GLFW_URL})

# set(IMGUI "https://github.com/ocornut/imgui/archive/refs/tags/v1.87.tar.gz")
# set(IMGUI "https://github.com/ocornut/imgui/archive/refs/tags/v1.87.zip")
# install_deps("imgui" "imgui_v1.87.zip" ${IMGUI})

# add FreeGLUT project
# set(SFML_BUILD_EXAMPLES FALSE)
# set(SFML_BUILD_DOC FALSE)
# add_subdirectory(${DEPS_DIR}/SFML-2.4.1)

# add FreeGLUT project
set(FREEGLUT_BUILD_DEMOS OFF)
add_subdirectory(${DEPS_DIR}/freeglut-3.2.2)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${DEPS_DIR}/glfw-3.3.6)
# target_link_libraries(myapp glfw)
# list(APPEND CMAKE_PREFIX_PATH "./dependencies/glfw-3.3.6/cmake")

# https://sdk.lunarg.com/sdk/download/1.3.204.0/windows/VulkanSDK-1.3.204.0-Installer.exe
# target_link_libraries(NAME Vulkan::Vulkan)
find_package (Vulkan)


find_path(SFML_FRAMEWORK "${SFML_VER}" "./dependencies/")
if(SFML_FRAMEWORK)
    set(SFML_ROOT "${SFML_FRAMEWORK}/${SFML_VER}")
    message("SFML Framework Found: " ${SFML_ROOT})
else()
    message("SFML Framework Not found: " ${SFML_VER})    
endif()

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")
list(APPEND CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH "${SFML_ROOT}/cmake/Modules/")
# list(APPEND CMAKE_PREFIX_PATH "c:/Program Files (x86)/freeglut/lib/cmake/FreeGLUT")
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

set(SFML_STATIC_LIBRARIES TRUE)
set(STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network main)
include_directories(${SFML_INCLUDE_DIR})
find_package(FreeGLUT)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_BUILD_TYPE Debug)

# gcc -Wl,--subsystem,windows
# set(CMAKE_EXE_LINKER_FLAGS "/subsystem:windows")
# add_link_options("/subsystem:windows")
# target_link_options(some_exe PUBLIC "/subsystem:windows")

# set(CMAKE_CXX_FLAGS "/MT")
# set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# add_definitions("/MT")
add_compile_options(/MTd)


string(TOLOWER ${CMAKE_BUILD_TYPE} BUILDTYPE)
if("${BUILDTYPE}" STREQUAL "release")
    set(BUILDTYPE "optimized")
    add_compile_options(/MT)
endif()
foreach(item ${SFML_LIBRARIES})
    if("${LASTITEM}" STREQUAL "${BUILDTYPE}" )
        message("${BUILDTYPE}:" ${item})
        set(SFML_LIBRARIES_CONFIG "${SFML_LIBRARIES_CONFIG}" "${item}")
    endif()
    set(LASTITEM ${item})
endforeach()
foreach(item ${SFML_DEPENDENCIES})
    # message("SFML_DEPENDENCIES:" ${item})
endforeach()


macro(add_sfml_executable NAME)
    message("executable: " ${NAME} [${ARGN}])
    add_executable(${NAME} ${ARGN})
    target_link_libraries(${NAME} ${SFML_LIBRARIES} opengl32 winmm )
    target_link_libraries(${NAME} ${SFML_DEPENDENCIES} )
endmacro()

macro(add_glut_executable NAME)
    message("executable: " ${NAME} [${ARGN}])
    add_executable(${NAME} ${ARGN})
    target_link_libraries(${NAME} opengl32 winmm gdi32 )
    target_link_libraries(${NAME} FreeGLUT::freeglut_static) 
    target_compile_options(${NAME} PUBLIC "/MD")
endmacro()

macro(add_glfw_executable NAME)
    message("executable: " ${NAME} [${ARGN}])
    add_executable(${NAME} ${ARGN})
    target_link_libraries(${NAME} opengl32 winmm gdi32 )
    target_link_libraries(${NAME} glfw Vulkan::Vulkan)
    target_compile_options(${NAME} PUBLIC "/MD")
endmacro()

add_sfml_executable(sfml_threads examples/sfml_threads.cpp)
add_sfml_executable(sfml_window examples/sfml_window.cpp)
add_sfml_executable(sfml_sprite examples/sfml_sprite.cpp)
add_sfml_executable(sfml_vertices examples/sfml_vertices.cpp)
add_sfml_executable(sfml_particles examples/sfml_particles.cpp)
add_sfml_executable(sfml_shaders examples/sfml_shaders.cpp)

add_executable(cpp_friends examples/cpp_friends.cpp)
add_executable(cpp_fileio examples/cpp_fileio.cpp)
add_executable(cpp_ostrich examples/cpp_ostrich.cpp)
add_executable(cpp_auto_construct examples/cpp_auto_construct.cpp)
add_executable(cpp_exception examples/cpp_exception.cpp)
add_executable(cpp_exception_copyctor examples/cpp_exception_copyctor.cpp)
add_executable(cpp_max examples/cpp_max.cpp)
add_executable(cpp_map examples/cpp_map.cpp)
add_executable(cpp_stack examples/cpp_stack.cpp)
add_executable(cpp_mi_virtual examples/cpp_mi_virtual.cpp)
add_executable(cpp_multiple_inheritance examples/cpp_multiple_inheritance.cpp)
add_executable(cpp_xman examples/cpp_xman.cpp)
add_executable(cpp_static_polymorphism examples/cpp_static_polymorphism.cpp)

add_glut_executable(freeglut_opengl examples/freeglut_opengl.cpp)
add_glfw_executable(glfw_base examples/glfw_base.cpp)

# No /subsystem:console, no console.
# target_link_options(sfml_shaders PUBLIC "/subsystem:windows")

if(MSVC)
    message("MSCV detected")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wunused-value -Wno-c++11-long-long -Wno-variadic-macros -Werror -Wextra -pedantic -Wnonportable-include-path -Wshadow -std=c89")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wunused-value -Wno-c++11-long-long -Wno-variadic-macros -Werror -Wextra -Wnon-virtual-dtor -pedantic -Wnonportable-include-path -Wshadow -std=c++11 -fno-exceptions -fno-rtti")
endif()

set(CMAKE_INSTALL_PREFIX "./")
set(CMAKE_VERBOSE_MAKEFILE ON)

# add_subdirectory(spine-c)
# add_subdirectory(c)

# add_subdirectory(spine-cpp)
# add_subdirectory(cpp)



# build spine-sfml demo and copy data to build directory
# include_directories(cpp/src )
# add_executable(spine-sfml-demo cpp/example/main.cpp)
# target_link_libraries(spine-sfml-demo spine-cpp spine-sfml-cpp)
# target_link_libraries(spine-sfml-demo ${SFML_LIBRARIES_CONFIG} opengl32 winmm )
# target_link_libraries(spine-sfml-demo ${SFML_DEPENDENCIES} )
# add_custom_command(TARGET spine-sfml-demo PRE_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_LIST_DIR}/cpp/data $<TARGET_FILE_DIR:spine-sfml-demo>/data)


# include(GNUInstallDirs)
# install(TARGETS sfml_window sfml_threads spine-sfml-demo
#         PUBLIC_HEADER
#         DESTINATION mybin
# )

# install(CODE "MESSAGE(\"::Sample install message. try cmake --install .\")")

# install(DIRECTORY spine-cpp/spine-cpp/ DESTINATION include/myproj
#         FILES_MATCHING PATTERN "*.h")
