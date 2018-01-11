# PhysicsFS; a portable, flexible file i/o abstraction.
#
# Please see the file LICENSE.txt in the source's root directory.

# The CMake project file is meant to get this compiling on all sorts of
#  platforms quickly, and serve as the way Unix platforms and Linux distros
#  package up official builds, but you don't _need_ to use this; we have
#  built PhysicsFS to (hopefully) be able to drop into your project and
#  compile, using preprocessor checks for platform-specific bits instead of
#  testing in here.

cmake_minimum_required(VERSION 2.8.4)

project(PhysicsFS)
set(PHYSFS_VERSION 3.0.1)

# Increment this if/when we break backwards compatibility.
set(PHYSFS_SOVERSION 1)

# I hate that they define "WIN32" ... we're about to move to Win64...I hope!
if(WIN32 AND NOT WINDOWS)
  set(WINDOWS TRUE)
endif()

include_directories(./src)

if(APPLE)
  set(OTHER_LDFLAGS ${OTHER_LDFLAGS} "-framework IOKit -framework Foundation")
  set(PHYSFS_M_SRCS src/physfs_platform_apple.m)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  # Don't use -rpath.
  set(CMAKE_SKIP_RPATH ON CACHE BOOL "Skip RPATH" FORCE)
endif()

if(CMAKE_C_COMPILER_ID STREQUAL "SunPro")
  add_definitions(-erroff=E_EMPTY_TRANSLATION_UNIT)
  add_definitions(-xldscope=hidden)
endif()

if(HAIKU)
  # We add this explicitly, since we don't want CMake to think this
  #  is a C++ project unless we're on Haiku.
  set(PHYSFS_CPP_SRCS src/physfs_platform_haiku.cpp)
  find_library(BE_LIBRARY be)
  find_library(ROOT_LIBRARY root)
  set(OPTIONAL_LIBRARY_LIBS ${OPTIONAL_LIBRARY_LIBS} ${BE_LIBRARY} ${ROOT_LIBRARY})
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "WindowsPhone" OR CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
  set(WINRT TRUE)
endif()

if(WINRT)
  set(PHYSFS_CPP_SRCS src/physfs_platform_winrt.cpp)
endif()

if(UNIX AND NOT WINDOWS AND NOT APPLE)  # (MingW and such might be UNIX _and_ WINDOWS!)
  find_library(PTHREAD_LIBRARY pthread)
  if(PTHREAD_LIBRARY)
    set(OPTIONAL_LIBRARY_LIBS ${OPTIONAL_LIBRARY_LIBS} ${PTHREAD_LIBRARY})
  endif()
endif()

# Almost everything is "compiled" here, but things that don't apply to the
#  build are #ifdef'd out. This is to make it easy to embed PhysicsFS into
#  another project or bring up a new build system: just compile all the source
#  code and #define the things you want.
set(PHYSFS_SRCS
  src/physfs.c
  src/physfs_byteorder.c
  src/physfs_unicode.c
  src/physfs_platform_posix.c
  src/physfs_platform_unix.c
  src/physfs_platform_windows.c
  src/physfs_platform_os2.c
  src/physfs_platform_qnx.c
  src/physfs_archiver_dir.c
  src/physfs_archiver_unpacked.c
  src/physfs_archiver_zip.c
  src/physfs_archiver_iso9660.c
  ${PHYSFS_CPP_SRCS}
  ${PHYSFS_M_SRCS}
  )

# Static library

add_library(physfs STATIC ${PHYSFS_SRCS})
# Don't rename this on Windows, since DLLs will also produce an import
#  library named "physfs.lib" which would conflict; Unix tend to like the
#  same library name with a different extension for static libs, but
#  Windows can just have a separate name.
if(NOT MSVC)
  set_target_properties(physfs PROPERTIES OUTPUT_NAME "physfs")
endif()
if(WINRT)
  # Ignore LNK4264 warnings; we don't author any WinRT components, just consume them, so we're okay in a static library.
  set_target_properties(physfs PROPERTIES VS_WINRT_COMPONENT True)
  set_target_properties(physfs PROPERTIES STATIC_LIBRARY_FLAGS "/ignore:4264")
endif()

set(PHYSFS_LIB_TARGET physfs)

# CMake FAQ says I need this...
if(NOT WINDOWS)
  set_target_properties(physfs PROPERTIES CLEAN_DIRECT_OUTPUT 1)
endif()

install(TARGETS ${PHYSFS_INSTALL_TARGETS}
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX})
install(FILES src/physfs.h DESTINATION include)

# end of CMakeLists.txt ...
