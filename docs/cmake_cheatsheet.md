# Cmake Cheatsheet

## Defining targets
`add_library(new_lib [source_files])` - defines new library depends on source files
`add_executable(new_exec [source_files])` - defines new executable depends on source files

## Defining dependency
`target_link_libraries(target [dependencies])` - defines that target depends on given libraries
`include_directories(include_dir)` - adds given dir into include path of **current and inherited CMakeList.txt** targets

## CMake control
`add_subdirectory(directory)` - adds given dir to CMake - it will looks for CMakeLists.txt inside it

## File listing
`file(command out_variable pattern)` - perform a file search operation: returns in *out_variable* files matching *pattern*
*command* can be:
- *GLOB* - search for files in current dir
- *GLOB_RECURSE* - search for files recursively


