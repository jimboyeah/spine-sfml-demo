cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(SFML_Win32)

find_path(SFML_FRAMEWORK "SFML-2.4.1" "../../dependencies/")
if(SFML_FRAMEWORK)
    set(SFML_ROOT "${SFML_FRAMEWORK}/SFML-2.4.1")
    message("SFML Framework 2.4.1 Found: " ${SFML_ROOT})
else()
    message("SFML Framework 2.4.1 Not found: " ${SFML_ROOT})    
endif()

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")
list(APPEND CMAKE_MODULE_PATH "${SFML_ROOT}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH "${SFML_ROOT}/cmake/Modules/")

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window audio network)
include_directories(${SFML_INCLUDE_DIR})

add_executable(sfml_win32 Windows.cpp)
target_link_libraries(sfml_win32 ${SFML_LIBRARIES} opengl32 winmm)

foreach(item ${SFML_LIBRARIES})
    message("SFML_LIBRARIES:" ${item})
endforeach()
foreach(item ${SFML_INCLUDE_DIR})
    message("SFML_INCLUDE_DIR:" ${item})
endforeach()
