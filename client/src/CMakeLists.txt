
add_subdirectory(model)
add_subdirectory(view)

add_library(clientCore Client.cpp MovementManager.cpp)
add_library(inputController KeyboardController.cpp  CommunicationService.cpp WorldUpdater.cpp)

add_executable(client clientMain.cpp)

target_link_libraries(inputController messages socketServices)
target_link_libraries(clientCore inputController model view)
target_link_libraries(client clientCore utilities)

