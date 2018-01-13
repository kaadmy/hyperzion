
# Source files

set(GAME_SOURCES
  game.cpp
  ship.cpp)

# Setup binary

add_library(game
  ${GAME_SOURCES})

target_link_libraries(game
  ${SHARED_LIBRARIES}
  common
  renderer)
