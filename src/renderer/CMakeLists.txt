
# Include libraries

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Source files

set(RENDERER_SOURCES
  program.cpp
  renderer.cpp
  vbo.cpp)

# Setup binary

add_library(renderer
  ${RENDERER_SOURCES})

target_link_libraries(renderer
  m # Math
  dl # DLopen
  ${GLFW_LIBRARIES}
  ${OPENGL_gl_LIBRARY})
