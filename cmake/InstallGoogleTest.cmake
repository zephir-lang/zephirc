include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.10.0)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# InstallGoogleTest.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
