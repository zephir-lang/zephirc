include(InstallGoogleTest)
include(GoogleTest)

file(GLOB PARSER_TEST_SOURCE_LIST ./*.parser.cpp)

add_executable(parser_tests main.cpp argv.cpp ${PARSER_TEST_SOURCE_LIST})

target_link_libraries(parser_tests PRIVATE commands gtest gtest_main)

gtest_discover_tests(parser_tests
                     PROPERTIES
                     LABELS
                     SelfTest)

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
