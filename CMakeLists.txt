cmake_minimum_required(VERSION 2.8)

project("ClientServer")

find_package(GTest REQUIRED)
if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(FATAL_ERROR, " GTest not found")
endif()

set(CURSES_NEED_NCURSES true)
find_package(Curses)
if(CURSES_FOUND)
    include_directories(${CURSES_INCLUDE_DIRS})
else()
    message(FATAL_ERROR, " Curses not found")
endif()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("common/external/cereal/include")

add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(server)

