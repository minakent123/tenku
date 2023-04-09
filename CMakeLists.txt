cmake_minimum_required(VERSION 3.24)
project(tenku CXX)

include(CMakeHelpers.cmake)

set(TARGET tenku)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
add_custom_target(prebuild_scripts)
run_code_format(prebuild_scripts)

file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(${TARGET} ${SRCS})
add_dependencies(${TARGET} prebuild_scripts)
target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/src)
