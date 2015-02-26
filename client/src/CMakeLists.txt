
add_subdirectory(model)

add_library(clientCore Client.cpp MovementManager.cpp)
add_library(inputController KeyboardController.cpp KeyGetter.cpp CommunicationService.cpp WorldUpdater.cpp)

add_executable(client clientMain.cpp)

target_link_libraries(inputController ncurses messages socketServices)
target_link_libraries(clientCore inputController model)
target_link_libraries(client clientCore utilities)

