# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(GoogleTest)

set(ZEPHIR_TESTS console_test config_test logger_test)
mark_as_advanced(ZEPHIR_TESTS)

# Global tests properties
configure_file(properties.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/properties.hpp")

# sharness setup script
configure_file(setup.sh.in "${CMAKE_CURRENT_SOURCE_DIR}/setup.sh")

file(GLOB_RECURSE CLI_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.options.cpp)
add_executable(console_test main.cpp ${CLI_TESTS})

target_include_directories(
  console_test
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(console_test PRIVATE console CONAN_PKG::GTest)

gtest_discover_tests(
  console_test
  TEST_PREFIX zephir:
  PROPERTIES LABELS OptionsTest)

file(GLOB CONFIG_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp)
add_executable(config_test main.cpp ${CONFIG_TESTS})

target_include_directories(
  config_test
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/config>)

target_link_libraries(config_test PRIVATE config filesystem CONAN_PKG::GTest)

gtest_discover_tests(
  config_test
  TEST_PREFIX zephir:
  PROPERTIES LABELS ConfigTest)

# LOGGER_TESTS
file(GLOB LOGGER_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/logger/*.cpp)
add_executable(logger_test main.cpp ${LOGGER_TESTS})

target_include_directories(
  logger_test
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    link_libraries("-lpthread")
endif()

target_link_libraries(logger_test PRIVATE logger CONAN_PKG::spdlog
                                          CONAN_PKG::GTest)

gtest_discover_tests(
  logger_test
  TEST_PREFIX zephir:
  PROPERTIES LABELS LoggerTest)

# End of LOGGER_TESTS

add_custom_target(
  check
  COMMAND ctest -j ${BUILD_JOBS} --output-on-failure
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS ${ZEPHIR_TESTS}
  COMMENT "Run all tests...")
