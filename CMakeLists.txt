cmake_minimum_required(VERSION 3.24)
project(tenku CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(CMakeHelpers)
include(SDL)

set(CMAKE_CXX_STANDARD 20)
set_common_variables()

set(TARGET tenku)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
add_custom_target(prebuild_scripts)
run_code_format(prebuild_scripts)

file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(${TARGET} ${SRCS})
add_dependencies(${TARGET} prebuild_scripts)
target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_sdl_properties(${TARGET})
