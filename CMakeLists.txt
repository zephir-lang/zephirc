# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

cmake_minimum_required(VERSION 3.11...3.16)

# Prepare VERSION variable
include(${CMAKE_SOURCE_DIR}/cmake/Version.cmake)

project(
  zephir
  LANGUAGES CXX
  VERSION ${ZEPHIR_VERSION}
  DESCRIPTION "A Zephir compiler")

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Options
option(CODE_COVERAGE "Builds targets with code coverage instrumentation." OFF)
option(ZEPHIR_BUILD_TESTING "Build test project" OFF)

# CMake Script Includes
include(Bootstrap)
include(CompilerOptions)
include(Cppcheck)
include(Formatting)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tools
file(
  GLOB_RECURSE
    FFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.[hc]
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.[hc]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[hc]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.[hc]
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.[hc]pp)
clang_format(cpp-format ${FFILES})

file(
  GLOB_RECURSE
    FFILES
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/*.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/external/*.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
cmake_format(cmake-format ${FFILES})

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_BINARY_DIR}"
      CACHE STRING "Directory to install zephir to" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Code Coverage Configuration
add_library(coverage_config INTERFACE)
add_library(zephir::coverage ALIAS coverage_config)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|(Apple)?[Cc]lang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE -O0 -g --coverage)

  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif()

add_subdirectory(external)
add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME
   AND BUILD_TESTING
   AND ZEPHIR_BUILD_TESTING)
  message(STATUS "Include test sources")
  add_subdirectory(tests)
endif()

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
