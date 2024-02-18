project(ut_File)

add_executable(${PROJECT_NAME}
    ut_File.cpp
)

add_test(
    ut_File
    ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PRIVATE narchiver::file
)
