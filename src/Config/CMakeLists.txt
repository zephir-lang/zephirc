# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for config library.
add_library(config SHARED Config.cpp)

target_include_directories(
  config
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(
  config
  PUBLIC CONAN_PKG::yaml-cpp filesystem
  PRIVATE zephir_warnings)

# Adds the library to the 'gcov' and 'lcov' targets
code_coverage(config)

# ##############################################################################
# Add definition for Context library
add_library(context SHARED Context.cpp)

target_include_directories(
  context
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(context PRIVATE zephir_warnings)

# Adds the library to the 'gcov' and 'lcov' targets
code_coverage(context)
