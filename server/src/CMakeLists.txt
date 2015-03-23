add_subdirectory(echoServer)
add_subdirectory(modules)

add_library(boostWrapper BoostWrapper.cpp)
add_library(socketServicesWrapper SocketServicesWrapper.cpp)
add_library(serverCore ServerInitializer.cpp)

add_executable(echoServer ServerMain.cpp)

target_link_libraries(serverCore boostWrapper messages utilities socketServices boost_system)
target_link_libraries(echoServer serverCore echoServerCore)

