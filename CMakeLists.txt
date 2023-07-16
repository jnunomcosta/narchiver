# Project setup
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(Narchiver LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake modules
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
)

# Options - WIP
# option(BUILD_UNIT_TESTS "Build unit tests" OFF)

# Default build type if build type not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include(CompileFlags)
set_default_compile_flags()

# Source inclusion
add_subdirectory(src)

# Testing here
# WIP

# Executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} narchiverlib)
