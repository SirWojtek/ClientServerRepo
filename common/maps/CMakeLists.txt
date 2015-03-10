
file(GLOB MAP_SOURCE "*.cpp")

add_library(maps ${MAP_SOURCE})

target_link_libraries(maps tmx-loader)
