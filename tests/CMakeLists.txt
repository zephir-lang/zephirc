# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

define_property(
  GLOBAL
  PROPERTY ZEPHIR_TESTS
  BRIEF_DOCS "All Zephir tests"
  FULL_DOCS "The full list of all Zephir tests")

set(ZEPHIR_TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Global tests properties
configure_file(Properties.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/Properties.hpp")

# sharness setup script
configure_file(setup.sh.in "${CMAKE_CURRENT_SOURCE_DIR}/setup.sh")

add_subdirectory(Config)
add_subdirectory(Console)
add_subdirectory(Logger)

if(NOT WIN32)
  add_test(
    NAME BlackboxTest
    COMMAND make
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

get_property(ZEPHIR_TESTS GLOBAL PROPERTY ZEPHIR_TESTS)
add_custom_target(
  check
  COMMAND ctest --output-on-failure
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS ${ZEPHIR_TESTS}
  COMMENT "Run all tests...")
