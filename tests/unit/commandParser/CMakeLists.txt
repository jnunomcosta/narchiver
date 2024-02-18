project(ut_CommandParser)

add_executable(${PROJECT_NAME}
    ut_CommandParser.cpp
)

add_test(
    ut_CommandParser
    ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PRIVATE narchiver::commandParser
)
