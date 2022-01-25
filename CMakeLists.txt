cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(UseMSVC "Using MSVC Compiler" ON)
if(UseMSVC)
    set(CMAKE_C_COMPILER cl.exe)
    set(CMAKE_CXX_COMPILER cl.exe)
    set(CMAKE_RC_COMPILER rc.exe)
    set(SFML_VER "SFML-2.4.1") # -vc14-64-bit
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
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})

set(SFML_STATIC_LIBRARIES TRUE)
set(STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio network)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS "/MT")
# set(CMAKE_CXX_FLAGS_RELEASE "/MT")

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

add_sfml_executable(sfml_threads examples/threads.cpp)
add_sfml_executable(sfml_window examples/window.cpp)
add_sfml_executable(sfml_sprite examples/sprite.cpp)
add_sfml_executable(sfml_vertices examples/vertices.cpp)
add_sfml_executable(sfml_particles examples/particles.cpp)
add_sfml_executable(sfml_shaders examples/shaders.cpp)
add_executable(cpp_friends examples/friends.cpp)
add_executable(cpp_ostrich examples/ostrich.cpp)


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
