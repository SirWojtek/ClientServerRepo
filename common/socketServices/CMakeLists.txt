
add_subdirectory(ut)

add_library(socketServices MessageQueue.cpp MessageReader.cpp MessageWriter.cpp TcpSocket.cpp)

target_link_libraries(socketServices utilities boost_system)
