set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR}/common/external/soci/src/backends/mysql -I${PROJECT_SOURCE_DIR}/common/external/soci/src/core -I /usr/include/mysql ${CMAKE_CXX_FLAGS}")

add_library(database MysqlDatabaseWrapper.cpp)

target_link_libraries(database)