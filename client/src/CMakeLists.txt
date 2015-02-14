
add_library(clientCore Client.cpp CommunicationService.cpp Console.cpp MessageQueue.cpp MessageReader.cpp MessageWriter.cpp TcpSocket.cpp)

add_executable(client clientMain.cpp)

target_link_libraries(clientCore common boost_system)
target_link_libraries(client clientCore)

