
cmake_minimum_required(VERSION 2.6)
project(nekogui)

#settings
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_USE_MATH_DEFINES=1)
set(NEKOGUI_API OPENGL CACHE BOOL "Game to build with")

# Deps
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/nekolib")

#lib
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(nekogui STATIC ${sources})
target_include_directories(nekogui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/neko/gui")
target_include_directories(nekogui PUBLIC nekolib)

target_link_libraries(nekogui PUBLIC nekolib)
