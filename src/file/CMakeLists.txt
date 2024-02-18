project(file)

add_library(${PROJECT_NAME} STATIC File.cpp)

add_library(narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC .)
