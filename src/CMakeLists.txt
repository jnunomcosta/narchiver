project(narchiverlib)

add_subdirectory(archiver)
add_subdirectory(common)
add_subdirectory(dearchiver)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Narchiver::archiver
    common
    Narchiver::dearchiver
)
