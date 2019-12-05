# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for filesystem library.
add_library(filesystem SHARED filesystem.cpp)

target_include_directories(
  filesystem PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Instruments the library
target_code_coverage(filesystem AUTO ALL)
