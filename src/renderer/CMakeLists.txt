
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
  ${GLFW_STATIC_LIBRARIES}
  ${OpenGL_STATIC_LIBRARIES})
