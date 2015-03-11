
add_subdirectory(mocks)
include_directories("mocks")
include_directories("${PROJECT_SOURCE_DIR}/common/socketServices/ut/mocks")


file(GLOB TEST_SOURCE "*.cpp")

add_executable(serverTest ${TEST_SOURCE})
target_link_libraries(serverTest utilities echoServerCore ${GTEST_BOTH_LIBRARIES} gmock)

