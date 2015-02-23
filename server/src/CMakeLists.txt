add_library(serverCore Server.cpp ServerSession.cpp)

add_executable(server ServerMain.cpp)

target_link_libraries(serverCore utilities boost_system)
target_link_libraries(server serverCore)

