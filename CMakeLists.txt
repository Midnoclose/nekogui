
cmake_minimum_required(VERSION 2.6)
project(nekogui)

set(CMAKE_CXX_STANDARD 17)
#set(OpenGL_GL_PREFERENCE GLVND)
add_definitions(-D_USE_MATH_DEFINES=1 ) # m64 for libglez

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(nekogui STATIC ${sources})
target_include_directories(nekogui PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/neko/gui")
target_include_directories(nekogui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/nekolib")
find_package(X11 REQUIRED)
find_package(Fontconfig REQUIRED)
target_include_directories(nekogui PUBLIC nekolib ${FREETYPE_INCLUDE_DIR_ft2build})
target_link_libraries(nekogui PUBLIC nekolib ${X11_LIBRARIES} ${Fontconfig_LIBRARIES})


# GL

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/libglez")
find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

add_definitions(-DNGUI_OPENGL=1 -DOGLFT_NO_SOLID=1 -DOGLFT_NO_QT=1 -ggdb -O0)
target_include_directories(nekogui PUBLIC glez )
target_link_libraries(nekogui PUBLIC glez ${OPENGL_LIBRARIES} OGLFT)
target_compile_options(glez PUBLIC -m64 -ggdb -O0)

# Example
add_executable(nekogui-example "${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp")
target_include_directories(nekogui-example PUBLIC nekogui)
target_link_libraries(nekogui-example PUBLIC nekogui)
