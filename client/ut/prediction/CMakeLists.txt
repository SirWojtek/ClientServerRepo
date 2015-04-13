
file(GLOB TEST_SOURCE "*.cpp")

add_executable(predictionTest ${TEST_SOURCE})
target_link_libraries(predictionTest prediction ${GTEST_BOTH_LIBRARIES})
