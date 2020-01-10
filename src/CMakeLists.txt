# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Zephir libraries
add_subdirectory(Console)
add_subdirectory(FileSystem)
add_subdirectory(Config)
add_subdirectory(Logger)

# Main
add_executable(zephir main.cpp)

target_include_directories(
  zephir
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(
  zephir
  PUBLIC console
  PRIVATE zephir_warnings)

# Adds the executable to the 'gcov' and 'lcov' targets
code_coverage(zephir)
