set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/common/external/soci/src/backends/mysql -I${PROJECT_SOURCE_DIR}/common/external/soci/src/core -I /usr/include/mysql ${CMAKE_CXX_FLAGS}")

add_subdirectory(mocks)
include_directories("mocks")

file(GLOB TEST_SOURCE "*.cpp")

add_executable(serverTest ${TEST_SOURCE})
target_link_libraries(serverTest utilities database echoServerCore ${GTEST_BOTH_LIBRARIES} gmock boost_system messages)

