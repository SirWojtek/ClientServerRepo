set(CMAKE_CXX_FLAGS "-fsanitize=null ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/common/external/soci/src/backends/mysql -I${PROJECT_SOURCE_DIR}/common/external/soci/src/core -I /usr/include/mysql ${CMAKE_CXX_FLAGS}")

add_subdirectory(echoServer)
add_subdirectory(fullServer)
add_subdirectory(modules)

add_library(boostWrapper BoostWrapper.cpp)
add_library(socketServicesWrapper SocketServicesWrapper.cpp)
add_library(serverCore ServerInitializer.cpp)

add_executable(echoServer ServerMain.cpp)
add_executable(fullServer ServerMain.cpp)

target_link_libraries(serverCore boostWrapper socketServicesWrapper messages utilities socketServices boost_system)
target_link_libraries(echoServer serverCore echoServerCore)
target_link_libraries(fullServer serverCore fullServerCore database)

