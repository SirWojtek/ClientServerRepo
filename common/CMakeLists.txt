
set(CMAKE_CXX_FLAGS "-Wno-reorder -Wno-unused-function  ${CMAKE_CXX_FLAGS}")

add_subdirectory(messages)
add_subdirectory(utilities)
add_subdirectory(socketServices)
add_subdirectory(maps)
add_subdirectory(external)
