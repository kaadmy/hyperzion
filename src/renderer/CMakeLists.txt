
# Source files

set(RENDERER_SOURCES
  camera.cpp
  glad.cpp
  material.cpp
  model.cpp
  program.cpp
  renderer.cpp
  texture.cpp
  vbo.cpp)

# Setup binary

add_library(renderer
  ${RENDERER_SOURCES})

target_link_libraries(renderer
  ${SHARED_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${OPENGL_LIBRARIES}
  common)
