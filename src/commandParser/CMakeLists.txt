project(commandParser)

add_library(${PROJECT_NAME} STATIC CommandParser.cpp)

add_library(narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC .)
