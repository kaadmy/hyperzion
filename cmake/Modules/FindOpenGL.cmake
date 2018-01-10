
# Find pkgconfig

find_package(PkgConfig REQUIRED)

# Find the package

pkg_search_module(OPENGL REQUIRED gl)
include_directories(${OPENGL_INCLUDE_DIRS})
