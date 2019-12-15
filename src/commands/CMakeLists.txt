# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for commands library.
file(GLOB CMD_FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmd_*.cpp)
add_library(commands SHARED commands.cpp formatter.cpp ${CMD_FILES})

target_include_directories(
  commands PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Instruments the library
target_code_coverage(commands AUTO ALL)

target_link_libraries(commands PUBLIC CONAN_PKG::CLI11 config)
