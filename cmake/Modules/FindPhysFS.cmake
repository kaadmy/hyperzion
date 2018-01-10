
# Allow using system libraries if found

option(ENABLE_SYSTEM_PHYSFS "Enable the use of system-wide PhysFS libraries." FALSE)

# So IDEs etc don't show these

mark_as_advanced(PHYSFS_LIBRARIES PHYSFS_INCLUDE_DIRS)

if(${ENABLE_SYSTEM_PHYSFS})
  # Check with pkgconfig

  find_package(PkgConfig REQUIRED)
  pkg_search_module(PHYSFS REQUIRED physfs>=3.0.0)

  if(${PHYSFS_FOUND})
    message(STATUS "System PhysFS found, using in place of bundle.")
  endif()
endif()

if((NOT ${PHYSFS_FOUND}) OR (NOT ${ENABLE_SYSTEM_PHYSFS}))
  message(STATUS "Using bundled PhysFS.")

  set(PHYSFS_LIBRARIES ${CMAKE_BINARY_DIR}/deps/physfs/libphysfs.a)
  set(PHYSFS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps/physfs/src)

  add_subdirectory(deps/physfs)
endif()

include_directories(${PHYSFS_INCLUDE_DIRS})
