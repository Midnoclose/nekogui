
set(CMAKE_CXX_STANDARD 17)

# gui mate
cmake_minimum_required(VERSION 2.6)
project(nekogui)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(nekogui STATIC ${sources})

set(NEKOGUI_API OPENGL CACHE BOOL "Game to build with")
# Dependancies
target_link_libraries(nekogui PUBLIC

# Example using xoverlay
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(PNG) # We need to link all this again since we prebuilt them staticly
find_package(GLEW)
find_package(OpenGL)
find_package(X11)
find_package(Freetype)
find_package(SDL2)
if(PNG_FOUND AND GLEW_FOUND AND OPENGL_FOUND AND X11_FOUND AND FREETYPE_FOUND)
  add_subdirectory(libglez)
  set_target_properties(glez PROPERTIES COMPILE_FLAGS "" LINK_FLAGS "")

  project(example)
  add_definitions(-g3 -ggdb)
  file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/example-src/*.c*")
  add_executable(example ${sources})

  # is longe

  example nekogui
                        "${CMAKE_CURRENT_SOURCE_DIR}/example-src/lib/libxoverlay.a"
                         ${PNG_LIBRARIES} GL GLU GLEW ${FREETYPE_LIBRARIES}
                         ${X11_X11_LIB} ${X11_Xext_LIB} ${X11_Xfixes_LIB})
  target_link_libraries(example glez)
endif()
# Wow ez
