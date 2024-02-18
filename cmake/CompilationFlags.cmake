macro(set_default_compile_flags)
    set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(CMAKE_CXX_EXTENSIONS OFF)

    add_compile_options(
        -pedantic
        -pedantic-errors
        -Wall
        -Wextra
    )

    add_compile_options(
        -D_GLIBCXX_ASSERTIONS
        -fstack-protector-strong
        -fwrapv
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wdouble-promotion
        -Wfloat-equal
        -Wformat=2
        -Wformat-security
        -Wmissing-include-dirs
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wredundant-decls
        -Wshadow
        -Wsign-conversion
        -Wuninitialized
        -Wunused-parameter
    )

    add_compile_options(
        "$<$<CONFIG:DEBUG>:-ftrapv>"
    )

    if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
        add_compile_options(
            -Walloc-zero
            -Walloca
            -Wduplicated-branches
            -Wduplicated-cond
            -Wformat-signedness
            -Wimplicit-fallthrough=5
            -Wlogical-op
            -Werror
        )

    else()
        add_compile_options(
            -Wno-gnu-zero-variadic-macro-arguments
            -Werror
        )
    endif()

    add_compile_options(-fstack-protector-all)

    if(NOT CMAKE_BUILD_TYPE MATCHES "^(Debug|Coverage)$")
        add_definitions(-D_FORTIFY_SOURCE=2)
    endif()
endmacro()
