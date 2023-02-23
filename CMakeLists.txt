cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(narchiver VERSION 1.0.0)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(narchiver_lib ${SOURCES})

add_executable(narchiver main.cpp)
target_link_libraries(narchiver narchiver_lib)