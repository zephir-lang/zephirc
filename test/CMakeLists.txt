include(InstallGoogleTest)
include(GoogleTest)

file(GLOB OPTIONS_TEST_SOURCE_LIST ./commands/*.options.cpp)

add_executable(options_test
    main.cpp
    argv.cpp
    ${OPTIONS_TEST_SOURCE_LIST})

target_link_libraries(options_test
    PRIVATE gtest commands)

gtest_discover_tests(options_test
    TEST_PREFIX       gtest:
    PROPERTIES        LABELS OptionsTest
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/commands")

# TODO: sharness tests
# if(NOT WIN32)
#     add_test(
#     NAME              Blackbox
#     COMMAND           make
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sharness")
# endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
