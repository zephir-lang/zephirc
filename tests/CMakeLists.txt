# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Conan bootstrap
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check(REQUIRED)

conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing)

include(GoogleTest)

set(ZEPHIR_TESTS options_test config_test)
mark_as_advanced(ZEPHIR_TESTS)

file(GLOB_RECURSE OPTIONS_TEST
     ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.options.cpp)
add_executable(options_test main.cpp env/base.cpp ${OPTIONS_TEST})

target_include_directories(
  options_test
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/commands>)

# Adds the executable to the 'ccov' and 'ccov-all' targets and excludes the file
# itself via regex
target_code_coverage(options_test AUTO ALL EXTERNAL)

target_link_libraries(options_test PRIVATE commands CONAN_PKG::GTest)

gtest_discover_tests(
  options_test
  TEST_PREFIX zephir:
  PROPERTIES LABELS OptionsTest)

file(GLOB_RECURSE CONFIG_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp)
add_executable(config_test main.cpp env/base.cpp ${CONFIG_TESTS})

target_include_directories(
  config_test
  PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# Adds the executable to the 'ccov' and 'ccov-all' targets and excludes the file
# itself via regex
target_code_coverage(config_test AUTO ALL EXTERNAL)

target_link_libraries(config_test PRIVATE config filesystem CONAN_PKG::GTest)

gtest_discover_tests(
  config_test
  TEST_PREFIX zephir:
  PROPERTIES LABELS ConfigTest)

add_custom_target(
  check
  COMMAND ctest -j ${BUILD_JOBS} --output-on-failure
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS ${ZEPHIR_TESTS}
  COMMENT "Run all tests...")

# cmake-format: off
# TODO: sharness tests
# if(NOT WIN32)
#     add_test(
#     NAME              BlackboxTest
#     COMMAND           make
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sharness")
# endif()
# cmake-format: on
