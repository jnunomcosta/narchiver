project(common LANGUAGES CXX)

add_subdirectory(file)
add_subdirectory(folder)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Narchiver::file
    Narchiver::folder
)
