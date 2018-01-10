
# Change binary location

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Source files

set(GAME_SOURCES
  main.cpp)

# Setup binary

add_executable(${CONFIG_GAME_NAME}
  ${GAME_SOURCES})

target_link_libraries(${CONFIG_GAME_NAME}
  ${SHARED_LIBRARIES}
  client)
