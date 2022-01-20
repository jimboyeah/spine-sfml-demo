cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(UseMSVC "Using MSVC Compiler" ON)
if(UseMSVC)
    set(CMAKE_C_COMPILER cl.exe)
    set(CMAKE_CXX_COMPILER cl.exe)
    set(CMAKE_RC_COMPILER rc.exe)
    set(SFML_VER "SFML-2.4.1-vc14-64-bit")
endif()

project(SFML_Win32 CXX)

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

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network)
include_directories(${SFML_INCLUDE_DIR})

add_executable(sfml_threads examples/threads.cpp)
target_link_libraries(sfml_threads ${SFML_LIBRARIES} opengl32 winmm)

add_executable(sfml_window examples/window.cpp)
target_link_libraries(sfml_window ${SFML_LIBRARIES} opengl32 winmm )
target_link_libraries(sfml_window ${SFML_DEPENDENCIES} )

foreach(item ${SFML_LIBRARIES})
    message("SFML_LIBRARIES:" ${item})
endforeach()
foreach(item ${SFML_DEPENDENCIES})
    message("SFML_DEPENDENCIES:" ${item})
endforeach()
