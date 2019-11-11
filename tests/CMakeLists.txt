# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

include(install-gtest)
include(GoogleTest)

file(GLOB OPTIONS_TEST_SOURCE_LIST
     ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.options.cpp)

add_executable(options_test main.cpp argv.cpp ${OPTIONS_TEST_SOURCE_LIST})

target_include_directories(options_test
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                  ${CMAKE_SOURCE_DIR}/src/commands
                                  ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(options_test PRIVATE gtest commands)

if(CODE_COVERAGE)
  target_code_coverage(options_test AUTO ALL)
endif()

gtest_discover_tests(options_test
                     TEST_PREFIX gtest:
                     PROPERTIES LABELS OptionsTest
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/commands)

# cmake-format: off
# TODO: sharness tests
# if(NOT WIN32)
#     add_test(
#     NAME              BlackboxTest
#     COMMAND           make
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sharness")
# endif()
# cmake-format: on

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
