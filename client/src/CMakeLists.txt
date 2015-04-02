
add_subdirectory(model)
add_subdirectory(view)
add_subdirectory(prediction)

add_library(clientCore Client.cpp MovementManager.cpp FilePositionWriter.cpp)
add_library(inputController KeyboardController.cpp  CommunicationService.cpp WorldUpdater.cpp LoginService.cpp)

add_executable(client clientMain.cpp)
add_executable(predictionBin predictionMain.cpp)

target_link_libraries(inputController messages socketServices)
target_link_libraries(clientCore inputController model view)
target_link_libraries(client clientCore utilities)

target_link_libraries(predictionBin prediction)
