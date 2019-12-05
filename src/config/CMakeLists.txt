# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for config library.
add_library(config SHARED config.cpp)

target_include_directories(
  config
  PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Instruments the library
target_code_coverage(config AUTO ALL)

target_link_libraries(config PUBLIC CONAN_PKG::yaml-cpp filesystem)
