add_library(serverCore ServerInitializer.cpp ServerSocket.cpp ServerSession.cpp)

add_executable(server ServerMain.cpp)

target_link_libraries(serverCore messages utilities socketServices boost_system)
target_link_libraries(server serverCore)

