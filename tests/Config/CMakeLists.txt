# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(GoogleTest)

file(GLOB CONFIG_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(ConfigTest ${ZEPHIR_TESTS_SOURCE_DIR}/main.cpp ${CONFIG_TESTS})
target_link_libraries(ConfigTest PRIVATE zephir_warnings)

target_include_directories(
  ConfigTest
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${ZEPHIR_TESTS_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(ConfigTest PRIVATE config filesystem CONAN_PKG::GTest)

gtest_discover_tests(
  ConfigTest
  TEST_PREFIX zephir:
  PROPERTIES LABELS ConfigTest)

set_property(GLOBAL APPEND PROPERTY ZEPHIR_TESTS ConfigTest)
