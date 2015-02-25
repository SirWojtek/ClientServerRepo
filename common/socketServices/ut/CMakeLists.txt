
add_subdirectory(mocks)
include_directories("mocks")

file(GLOB TEST_SOURCE "*.cpp")

add_executable(socketServiceTest ${TEST_SOURCE})
target_link_libraries(socketServiceTest socketServices ${GTEST_BOTH_LIBRARIES} gmock)
