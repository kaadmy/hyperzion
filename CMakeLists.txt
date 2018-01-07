
cmake_minimum_required(VERSION 2.8)

project(hyperzion CXX)

# Options

option(DEBUG_BUILD "Make a debug build" ON)

if(${DEBUG_BUILD})
  set(DEBUG_FLAGS "-O0 -g") # No optimization, keep debug symbols
else()
  set(DEBUG_FLAGS "-O3") # Optimization enabled
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ${DEBUG_FLAGS}")

# Generate config variables

set(CONFIG_GAME_NAME "hyperzion")
set(CONFIG_GAME_TITLE "Hyperzion")

set(CONFIG_VERSION_MAJOR 0)
set(CONFIG_VERSION_MINOR 1)
set(CONFIG_VERSION_PATCH 0)

configure_file(
  "${hyperzion_SOURCE_DIR}/src/config.h.in"
  "${hyperzion_SOURCE_DIR}/src/config.h")

# Load PkgConfig

find_package(PkgConfig REQUIRED)

# Local shared includes

set(SHARED_LIBRARIES
  m # Math
  dl # DLopen
  )

include_directories(src) # So files in src/ can be found when #including

# Renderer

add_subdirectory(src/renderer)

# Game

add_subdirectory(src/game)

# Main

add_subdirectory(src/main)
