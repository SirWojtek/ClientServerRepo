add_library(echoServerCore ServerInitializer.cpp ServerSocket.cpp echoServer/ServerSession.cpp)

add_executable(echoServer ServerMain.cpp)

target_link_libraries(echoServerCore messages utilities socketServices boost_system)
target_link_libraries(echoServer echoServerCore)

