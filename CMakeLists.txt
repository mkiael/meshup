cmake_minimum_required(VERSION 3.14)

project(meshup)

enable_testing()

include(external/external.cmake)

add_subdirectory(lib)
add_subdirectory(app)
