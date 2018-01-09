
# Headers

include_directories(./)
include_directories(${hyperzion_BINARY_DIR}/src) # For revision.h

# Modules

add_subdirectory(common)
add_subdirectory(renderer)
add_subdirectory(game)
add_subdirectory(client)

# Main

add_subdirectory(main)

# Git revision

add_custom_target(gitrevision ALL)

# creates svnversion.h using cmake script
add_custom_command(TARGET gitrevision COMMAND ${CMAKE_COMMAND}
   -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}
   -P ${CMAKE_CURRENT_SOURCE_DIR}/revision.cmake)
