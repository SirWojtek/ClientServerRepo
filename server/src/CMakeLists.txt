add_library(serverCore Server.cpp)

add_executable(server serverMain.cpp)

target_link_libraries(serverCore utilities boost_system)
target_link_libraries(server serverCore)

