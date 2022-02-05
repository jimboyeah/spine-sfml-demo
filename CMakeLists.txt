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
list(APPEND CMAKE_PREFIX_PATH "c:/Program Files (x86)/freeglut/lib/cmake/FreeGLUT")
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

set(SFML_STATIC_LIBRARIES TRUE)
set(STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network main)
find_package(FreeGLUT)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_BUILD_TYPE Release)

# gcc -Wl,--subsystem,windows
# set(CMAKE_EXE_LINKER_FLAGS "/subsystem:windows")
# add_link_options("/subsystem:windows")
# target_link_options(some_exe PUBLIC "/subsystem:windows")

# set(CMAKE_CXX_FLAGS "/MT")
# set(CMAKE_CXX_FLAGS_RELEASE "/MT")
# add_definitions("/MT")
add_compile_options(/MT)

string(TOLOWER ${CMAKE_BUILD_TYPE} BUILDTYPE)
if("${BUILDTYPE}" STREQUAL "release")
    set(BUILDTYPE "optimized")
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
    target_link_libraries(${NAME} FreeGLUT::freeglut_static opengl32 winmm gdi32 )
    message("FreeGLUT: " FreeGLUT::freeglut_static)
    target_compile_options(${NAME} PUBLIC "/MD")
endmacro()

add_sfml_executable(sfml_threads examples/threads.cpp)
add_sfml_executable(sfml_window examples/window.cpp)
add_sfml_executable(sfml_sprite examples/sprite.cpp)
add_sfml_executable(sfml_vertices examples/vertices.cpp)
add_sfml_executable(sfml_particles examples/particles.cpp)
add_sfml_executable(sfml_shaders examples/shaders.cpp)
add_glut_executable(freeglut_opengl examples/opengl.cpp)
add_executable(cpp_friends examples/friends.cpp)
add_executable(cpp_fileio examples/fileio.cpp)
add_executable(cpp_ostrich examples/ostrich.cpp)
add_executable(cpp_auto_construct examples/auto_construct.cpp)
add_executable(cpp_exception examples/exception.cpp)
add_executable(cpp_exception_copyctor examples/exception_copyctor.cpp)
add_executable(cpp_max examples/max.cpp)
add_executable(cpp_map examples/map.cpp)
add_executable(cpp_stack examples/stack.cpp)
add_executable(cpp_mi_virtual examples/mi_virtual.cpp)
add_executable(cpp_multiple_inheritance examples/multiple_inheritance.cpp)
add_executable(cpp_xman examples/xman.cpp)
add_executable(cpp_static_polymorphism examples/static_polymorphism.cpp)

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
