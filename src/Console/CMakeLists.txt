# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for cli library.
file(GLOB CLI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Commands/*.cpp)
add_library(console SHARED Formatter.cpp Application.cpp ${CLI_FILES})

target_include_directories(
  console
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(console PUBLIC CONAN_PKG::CLI11 config)

# Adds the library to the 'gcov' and 'lcov' targets
code_coverage(console)
