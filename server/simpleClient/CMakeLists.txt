
# add_subdirectory(model)

add_library(simpleClientCore Client.cpp CommunicationService.cpp KeyboardController.cpp)
add_library(simpleInputController KeyboardController.cpp KeyGetter.cpp)

add_executable(simpleClient clientMain.cpp)

target_link_libraries(simpleInputController ncurses)
target_link_libraries(simpleClientCore messages utilities socketServices boost_system simpleInputController)
target_link_libraries(simpleClient simpleClientCore)

