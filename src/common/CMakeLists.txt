
# Source files

set(COMMON_SOURCES
  file.cpp
  filesystem.cpp)

# Setup binary

add_library(common
  ${COMMON_SOURCES})

target_link_libraries(common
  ${SHARED_LIBRARIES}
  ${PHYSFS_LIBRARIES})
