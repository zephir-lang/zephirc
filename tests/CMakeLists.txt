# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

include(install-gtest)
include(GoogleTest)

file(GLOB TESTSF ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.options.cpp)
add_executable(options_test main.cpp argv.cpp env/base.cpp ${TESTSF})

target_include_directories(
  options_test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          ${CMAKE_SOURCE_DIR}/src/commands)

target_link_libraries(options_test PRIVATE gtest commands)
target_code_coverage(options_test AUTO ALL EXCLUDE ${COVERAGE_EXCLUDES})

gtest_discover_tests(
  options_test
  TEST_PREFIX gtest:
  PROPERTIES LABELS OptionsTest)

file(GLOB TESTSF ${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp)
add_executable(config_test main.cpp argv.cpp env/base.cpp ${TESTSF})

target_include_directories(
  config_test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          ${CMAKE_SOURCE_DIR}/src/config)

target_link_libraries(config_test PRIVATE gtest)
target_link_libraries(config_test PUBLIC config)
target_code_coverage(config_test AUTO ALL EXCLUDE ${COVERAGE_EXCLUDES})

gtest_discover_tests(
  config_test
  TEST_PREFIX gtest:
  PROPERTIES LABELS ConfigTest)

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
