
# Find pkgconfig

find_package(PkgConfig REQUIRED)

# Find the package

pkg_search_module(GLFW REQUIRED glfw3>=3.2.1)
include_directories(${GLFW_STATIC_INCLUDE_DIRS})
