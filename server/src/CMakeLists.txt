add_subdirectory(echoServer)

add_library(serverCore ServerInitializer.cpp ServerSocket.cpp)

add_executable(echoServer ServerMain.cpp)

target_link_libraries(serverCore messages utilities socketServices boost_system)
target_link_libraries(echoServer serverCore echoServerCore)

