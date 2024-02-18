project(ut_Folder)

add_executable(${PROJECT_NAME}
    ut_Folder.cpp
)

add_test(
    ut_Folder
    ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PUBLIC narchiver::folder
)
