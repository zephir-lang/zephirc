# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

set(SPDLOG_STATIC_LIBRARY ON)
find_package(SPDLOG REQUIRED)

# Add definition for logger facade library.
add_library(logger STATIC facade.cpp)

target_include_directories(
  logger
  PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
          ${SPDLOG_INCLUDE_DIR}
  PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(logger PRIVATE ${SPDLOG_LIBRARY})

target_code_coverage(logger AUTO ALL)

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
