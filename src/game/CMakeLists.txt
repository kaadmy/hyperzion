
# Include libraries

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Source files

set(GAME_SOURCES
  game.cpp)

# Setup binary

add_library(game
  ${GAME_SOURCES})

target_link_libraries(game
  m # Math
  dl # DLopen
  ${GLFW_LIBRARIES}
  renderer)
