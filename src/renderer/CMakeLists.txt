
# Include libraries

pkg_search_module(OpenGL REQUIRED gl)
include_directories(${OpenGL_STATIC_INCLUDE_DIRS})

# Source files

set(RENDERER_SOURCES
  glad.cpp
  program.cpp
  renderer.cpp
  vbo.cpp)

# Setup binary

add_library(renderer
  ${RENDERER_SOURCES})

target_link_libraries(renderer
  m # Math
  dl # DLopen
  ${OpenGL_STATIC_LIBRARIES})
