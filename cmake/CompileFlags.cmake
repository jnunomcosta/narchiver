#
# Set global compile flags for all targets in the project.
#
macro(set_default_compile_flags)
    set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # ... but not the compiler-specific variant
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
        -Wswitch-enum
        -Wuninitialized
        -Wunused-parameter
    )

    # Add compile options only needed on DEBUG builds
    add_compile_options(
        "$<$<CONFIG:DEBUG>:-ftrapv>"
    )

    # Add options supported by GNU
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

        # See https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html and
        # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
        link_libraries(-Wl,-z,noexecstack)

    else()
        add_compile_options(
            -Wno-gnu-zero-variadic-macro-arguments
            -Werror
        )
    endif()

    # For security

    # See https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html and
    # https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
    add_compile_options(-fstack-protector-all)

    # https://wiki.debian.org/Hardening#DEB_BUILD_HARDENING_RELRO_.28ld_-z_relro.29
    # https://wiki.debian.org/Hardening#DEB_BUILD_HARDENING_BINDNOW_.28ld_-z_now.29
    link_libraries(
        "-Wl,-z,relro"
        "-Wl,-z,now"
    )

    # https://gcc.gnu.org/ml/gcc-patches/2004-09/msg02055.html
    if(NOT CMAKE_BUILD_TYPE MATCHES "^(Debug|Coverage)$")
        add_definitions(-D_FORTIFY_SOURCE=2)
    endif()
endmacro()
