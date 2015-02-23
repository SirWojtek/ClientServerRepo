
add_subdirectory(model)

add_library(clientCore Client.cpp CommunicationService.cpp MessageQueue.cpp MessageReader.cpp MessageWriter.cpp TcpSocket.cpp)

add_executable(client clientMain.cpp)

target_link_libraries(clientCore common utilities boost_system)
target_link_libraries(client clientCore model)

