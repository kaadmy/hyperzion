
cmake_minimum_required(VERSION 2.8)

project(hyperzion CXX)

# Disable common warnings

option(SHOW_ALL_WARNINGS "Show all warnings" OFF)

if(${SHOW_ALL_WARNINGS})
  set(WARNING_FLAGS "-Wall -Wextra")
else()
  set(WARNING_FLAGS "-Wall")
endif()

# Debug build

option(DEBUG_BUILD "Make a debug build" ON)

if(${DEBUG_BUILD})
  set(DEBUG_FLAGS "-O0 -g") # No optimization, keep debug symbols
else()
  set(DEBUG_FLAGS "-O3") # Optimization enabled
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${DEBUG_FLAGS}")

# Generate config variables

set(CONFIG_ORG_NAME "kaadmy")

set(CONFIG_GAME_NAME "hyperzion")
set(CONFIG_GAME_TITLE "Hyperzion")

set(CONFIG_VERSION_MAJOR 0)
set(CONFIG_VERSION_MINOR 1)
set(CONFIG_VERSION_PATCH 0)

set(CONFIG_VERSION_STRING "${CONFIG_VERSION_MAJOR}.${CONFIG_VERSION_MINOR}.${CONFIG_VERSION_PATCH}")

set(CONFIG_PATH_DATA "data")

configure_file(
  "${hyperzion_SOURCE_DIR}/src/config.h.in"
  "${hyperzion_SOURCE_DIR}/src/config.h")

# Find libraries (optionally bundled)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(GLFW)
find_package(OpenGL)
find_package(PhysFS)

# Local shared includes

set(SHARED_LIBRARIES
  m # Math library
  dl # DLL library
  pthread # POXIS thread library
  )

# Source

add_subdirectory(src)
