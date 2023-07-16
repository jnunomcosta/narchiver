project(archiver LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE Archiver.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE .
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC common
)

add_library(Narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
