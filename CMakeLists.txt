
cmake_minimum_required(VERSION 2.8)

# Create configuration variables

set(CONFIG_ORG_NAME "kaadmy")

set(CONFIG_GAME_NAME "hyperzion")
set(CONFIG_GAME_TITLE "Hyperzion")

set(CONFIG_VERSION_MAJOR 0)
set(CONFIG_VERSION_MINOR 1)
set(CONFIG_VERSION_PATCH 0)

set(CONFIG_VERSION_STRING "${CONFIG_VERSION_MAJOR}.${CONFIG_VERSION_MINOR}.${CONFIG_VERSION_PATCH}")

set(CONFIG_PATH_DATA "data")

# Project declaration

project(${CONFIG_GAME_NAME} CXX)

# Disable common warnings

option(ENABLE_MORE_WARNINGS "Show all warnings" OFF)

if(${ENABLE_MORE_WARNINGS})
  set(WARNING_FLAGS "-Wall -Wextra")
else()
  set(WARNING_FLAGS "-Wall")
endif()

# Debug build

option(ENABLE_DEBUG "Make a debug build" ON)

if(${ENABLE_DEBUG})
  set(DEBUG_FLAGS "-O0 -g") # No optimization, keep debug symbols
else()
  set(DEBUG_FLAGS "-O3") # Optimization enabled
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${DEBUG_FLAGS}")

# Verbose mode

option(ENABLE_VERBOSE "Enable verbose logging" OFF)

if(${ENABLE_VERBOSE})
  set(CONFIG_VERBOSE 1)
else()
  set(CONFIG_VERBOSE 0)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${DEBUG_FLAGS}")

# Generate config file

configure_file(
  "${hyperzion_SOURCE_DIR}/src/config.h.in"
  "${hyperzion_SOURCE_DIR}/src/config.h")

# Find libraries (optionally bundled)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

include(FindGLFW)
include(FindOpenGL)
include(FindPhysFS)

# Local shared includes

set(SHARED_LIBRARIES
  m # Math library
  dl # DLL library
  pthread # POXIS thread library
  )

# Source

add_subdirectory(src)

# Display build configuration

macro(message_bool _NAME _VALUE)
  if (${_VALUE})
    message(STATUS "  ${_NAME}: yes")
  else()
    message(STATUS "  ${_NAME}: no")
  endif()
endmacro()

message(STATUS "Build configuration:")
message_bool("Show more warnings" ENABLE_MORE_WARNINGS)
message_bool("Debug build" ENABLE_DEBUG)
message_bool("Verbose logging" ENABLE_VERBOSE)
