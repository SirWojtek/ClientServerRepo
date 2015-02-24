
add_subdirectory(model)

add_library(clientCore Client.cpp CommunicationService.cpp KeyboardController.cpp)
add_library(inputController KeyboardController.cpp KeyGetter.cpp)

add_executable(client clientMain.cpp)

target_link_libraries(inputController ncurses)
target_link_libraries(clientCore common utilities socketServices boost_system inputController)
target_link_libraries(client clientCore model)

