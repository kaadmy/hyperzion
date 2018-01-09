
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

# Load PkgConfig

find_package(PkgConfig REQUIRED)

# Find and libraries

pkg_search_module(OpenGL REQUIRED gl)
include_directories(${OpenGL_STATIC_INCLUDE_DIRS})

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_STATIC_INCLUDE_DIRS})

pkg_search_module(PhysFS REQUIRED physfs)
include_directories(${PhysFS_STATIC_INCLUDE_DIRS})

# Local shared includes

set(SHARED_LIBRARIES
  m # Math
  dl # DLopen
  )

# Source

add_subdirectory(src)
