cmake_minimum_required(VERSION 3.0)

project(OpenGL)

# for debug cmake
# set(CMAKE_VERBOSE_MAKEFILE ON)

# for vscode c/c++ extend
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB_RECURSE LIBS lib/*.c(c|pp))
aux_source_directory(src DIR_SRCS)
list(APPEND DIR_SRCS ${LIBS})

find_package(glfw3 REQUIRED)

add_executable(main ${DIR_SRCS})
target_compile_options(main PUBLIC -g)
target_link_libraries(main glfw)