# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(install-gtest)
include(GoogleTest)

file(GLOB OPTIONS_TEST_SOURCE_LIST ./commands/*.options.cpp)

add_executable(options_test
    main.cpp
    ${OPTIONS_TEST_SOURCE_LIST})

target_link_libraries(options_test
    PRIVATE gtest commands)

if(CODE_COVERAGE)
    target_code_coverage(options_test AUTO ALL)
endif()

gtest_discover_tests(options_test
    TEST_PREFIX       gtest:
    PROPERTIES        LABELS OptionsTest
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/commands")

# TODO: sharness tests
# if(NOT WIN32)
#     add_test(
#     NAME              BlackboxTest
#     COMMAND           make
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sharness")
# endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
