cmake_minimum_required(VERSION 3.0)

project(OpenGL)

# for debug cmake
# set(CMAKE_VERBOSE_MAKEFILE ON)

# for vscode c/c++ extend
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa -framework IOKit")
endif()

include_directories(include)

file(GLOB_RECURSE LIBS lib/*.c lib/*.cpp)

if (NOT WIN32)
    find_package(glfw3 REQUIRED)
elseif (WIN32)
    link_directories(lib)
endif()

add_compile_definitions(STB_IMAGE_IMPLEMENTATION)
add_executable(main ${LIBS} src/main.cpp src/shader.cpp src/graphic.cpp src/sprite.cpp src/rect.cpp src/ui.cpp src/ui.h src/circle.cpp src/circle.h)
target_compile_options(main PUBLIC -g)
target_link_libraries(main glfw)