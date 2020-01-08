# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Adds support for multithreading with the pthreads library GNU gcc compiler
find_package(Threads REQUIRED)

include(GoogleTest)

file(GLOB LOGGER_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(LoggerTest ${ZEPHIR_TESTS_SOURCE_DIR}/main.cpp ${LOGGER_TESTS})

target_include_directories(
  LoggerTest
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  PRIVATE $<BUILD_INTERFACE:${ZEPHIR_TESTS_SOURCE_DIR}>
          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(LoggerTest PRIVATE logger CONAN_PKG::spdlog
                                         CONAN_PKG::GTest)

# must use explicit CXX flag for proper linker process
if(CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(LoggerTest PRIVATE -pthread)
endif()

gtest_discover_tests(
  LoggerTest
  TEST_PREFIX zephir:
  PROPERTIES LABELS LoggerTest)

set_property(GLOBAL APPEND PROPERTY ZEPHIR_TESTS LoggerTest)
