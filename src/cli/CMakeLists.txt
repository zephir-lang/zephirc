# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for commands library. file(GLOB CLI_FILES
# ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(cli SHARED application.cpp formatter.cpp)

target_include_directories(
  cli PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
             $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Instruments the library
target_code_coverage(cli AUTO ALL)

target_link_libraries(cli PUBLIC CONAN_PKG::CLI11 config)
