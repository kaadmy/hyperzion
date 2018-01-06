
# Change binary location

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include libraries

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Source files

set(GAME_SOURCES
  main.cxx
  glad.c
  renderer.cxx)

# Setup binary

add_executable(${CONFIG_GAME_NAME}
  ${GAME_SOURCES})

target_link_libraries(${CONFIG_GAME_NAME}
  m # Math
  dl # DLopen
  ${GLFW_LIBRARIES}
  ${OPENGL_gl_LIBRARY})
