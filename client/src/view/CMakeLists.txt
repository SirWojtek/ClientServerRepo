
file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_library(view ${SRC_FILES})

target_link_libraries(view ${SFML_LIBRARIES})
