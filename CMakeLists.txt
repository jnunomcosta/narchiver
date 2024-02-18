# Project setup
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(narchiver LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake modules
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
)

# Options
option(BUILD_NARCHIVER_UNIT_TESTS "Build unit tests" OFF)

# Default build type if build type not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(BUILD_NARCHIVER_UNIT_TESTS ON)
endif()

include(CompilationFlags)
set_default_compile_flags()

include(FetchDependencies)

# Source inclusion
add_subdirectory(src)

# Testing
if(BUILD_NARCHIVER_UNIT_TESTS)
    include(CTest)
    fetch_gtest()
    enable_testing()
    add_subdirectory(tests)
endif()

# Executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    PUBLIC narchiver::folder
    PUBLIC narchiver::commandParser)
