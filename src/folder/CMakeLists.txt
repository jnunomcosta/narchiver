project(folder)

add_library(${PROJECT_NAME} STATIC Folder.cpp)

add_library(narchiver::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME}
    PUBLIC narchiver::file
)
