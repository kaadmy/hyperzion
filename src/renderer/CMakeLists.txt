
# Source files

set(RENDERER_SOURCES
  glad.cpp
  material.cpp
  program.cpp
  renderer.cpp
  vbo.cpp)

# Setup binary

add_library(renderer
  ${RENDERER_SOURCES})

target_link_libraries(renderer
  ${SHARED_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${OPENGL_LIBRARIES})
