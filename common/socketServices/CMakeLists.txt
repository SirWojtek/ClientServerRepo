
add_library(socketServices MessageQueue.cpp MessageReader.cpp MessageWriter.cpp TcpSocket.cpp)

target_link_libraries(socketServices boost_system)
