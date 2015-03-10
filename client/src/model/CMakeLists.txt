
add_subdirectory(objects)

file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_library(model ${SRC_FILES})

target_link_libraries(model maps)
