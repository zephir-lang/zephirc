# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

set(SPDLOG_STATIC_LIBRARY ON)
find_package(spdlog CONFIG REQUIRED)

# Add definition for logger facade library.
add_library(logger STATIC facade.cpp)

target_include_directories(
  logger
  PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
          ${SPDLOG_INCLUDE_DIR}
  PUBLIC ${CMAKE_SOURCE_DIR}/src)

if(SPDLOG_BUILD_EXAMPLE_HO)
    # Using header-only spdlog library
    target_link_libraries(logger PRIVATE spdlog::spdlog_header_only)
else()
    # Using pre-compiled spdlog library
    target_link_libraries(logger PRIVATE spdlog::spdlog)
endif()

target_code_coverage(logger AUTO ALL)

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
