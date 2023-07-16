project(file LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE File.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE .
)

add_library(Narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
