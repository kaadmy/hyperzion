
# Source files

set(CLIENT_SOURCES
  client.cpp
  event.cpp)

# Setup binary

add_library(client
  ${CLIENT_SOURCES})

target_link_libraries(client
  ${SHARED_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  common
  game
  renderer)
