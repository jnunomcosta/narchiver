include(FetchContent)

function(fetch_gtest)
    fetchcontent_declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
    )
    fetchcontent_makeavailable(googletest)
    include(GoogleTest)
endfunction()
