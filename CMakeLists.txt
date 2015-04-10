cmake_minimum_required(VERSION 2.8)

project("ClientServer")


# variables needed to find Boost and GTest
set(BOOST_ROOT "/usr")
set(GTEST_ROOT "/usr")
set(BOX2D_INCLUDE_DIR "/usr/include")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Boost 1.57)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR, " Boost not found or it is too old")
endif()

find_package(GTest REQUIRED)
if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(FATAL_ERROR, " GTest not found")
endif()

find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
else()
    message(FATAL_ERROR, " SFML not found")
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
elseif(NOT ZLIB_FOUND)
    message("\n-> zlib directory not found. Set ZLIB_ROOT to zlib's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the zlib libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

find_package(BOX2D)
if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
elseif(NOT BOX2D_FOUND)
    message("\n-> Box2D directories not found. Set BOX2D_INCLUDE_DIR to Box2D's include path and BOX2D_LIBRARIES to Box2D's lib directory path.")
    message("-> Make sure the Box2D libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -pthread")


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("common/external/cereal/include")
include_directories("common/external/tmxloader/include")

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(common)


enable_testing()

# add test binaries here
add_test(clientTest bin/clientTest)
add_test(socketServiceTest bin/socketServiceTest)
add_test(serverCoreTest bin/serverCoreTest)
add_test(echoServerTest bin/echoServerTest)
add_test(fullServerTest bin/fullServerTest)