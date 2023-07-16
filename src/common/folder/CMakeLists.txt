project(folder LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE Folder.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE .
)

add_library(Narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC Narchiver::file
)
