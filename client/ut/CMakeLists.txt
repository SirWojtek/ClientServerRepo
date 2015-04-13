
add_subdirectory(mocks)
include_directories("mocks")
include_directories("${PROJECT_SOURCE_DIR}/common/socketServices/ut/mocks")


file(GLOB TEST_SOURCE "*.cpp")

add_executable(clientTest ${TEST_SOURCE})
target_link_libraries(clientTest utilities clientCore ${GTEST_BOTH_LIBRARIES} gmock)

add_subdirectory(prediction)
