# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# Add definition for commands library.
add_library(commands STATIC commands.cpp formatter.cpp)

target_include_directories(
  commands PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(commands PUBLIC CLI11)

if(CODE_COVERAGE)
  target_code_coverage(commands AUTO ALL)
endif()

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
