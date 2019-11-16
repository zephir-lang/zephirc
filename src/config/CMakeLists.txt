# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

set(YAMLCPP_STATIC_LIBRARY ON)
find_package(YAMLCPP REQUIRED)

# Add definition for config library.
add_library(config STATIC config.cpp)

target_include_directories(
  config
  PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
          ${YAMLCPP_INCLUDE_DIR}
  PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(config PRIVATE ${YAMLCPP_LIBRARY} filesystem commands)

if(CODE_COVERAGE)
  target_code_coverage(config AUTO ALL)
endif()

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
