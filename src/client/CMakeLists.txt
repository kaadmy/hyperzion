
# Include libraries

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Source files

set(CLIENT_SOURCES
  client.cpp)

# Setup binary

add_library(client
  ${CLIENT_SOURCES})

target_link_libraries(client
  ${SHARED_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  game
  renderer)
