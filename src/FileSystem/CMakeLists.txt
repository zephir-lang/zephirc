# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for filesystem library.
add_library(filesystem SHARED FileSystem.cpp)

target_include_directories(
  filesystem PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Adds the library to the 'gcov' and 'lcov' targets
code_coverage(filesystem)
