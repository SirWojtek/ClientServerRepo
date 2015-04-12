set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/common/external/soci/src/backends/mysql -I${PROJECT_SOURCE_DIR}/common/external/soci/src/core -I /usr/include/mysql ${CMAKE_CXX_FLAGS}")

add_subdirectory(mocks)
include_directories("mocks")

file(GLOB TEST_SOURCE "*.cpp")

add_executable(serverCoreTest MysqlDatabaseWrapperTests.cpp ServerInitializerTests.cpp SocketServicesWrapperTests.cpp)
add_executable(echoServerTest EchoServerSessionTests.cpp)
add_executable(fullServerTest FullServerSessionTests.cpp)

target_link_libraries(serverCoreTest serverCore echoServerCore database ${GTEST_BOTH_LIBRARIES} gmock)
target_link_libraries(echoServerTest serverCore echoServerCore database ${GTEST_BOTH_LIBRARIES} gmock)
target_link_libraries(fullServerTest serverCore fullServerCore database ${GTEST_BOTH_LIBRARIES} gmock)

