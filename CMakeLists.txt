# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

cmake_minimum_required(VERSION 3.11...3.16)

# Prepare VERSION variable
include("${CMAKE_SOURCE_DIR}/cmake/version.cmake")

project(zephir
    LANGUAGES   CXX
    VERSION     "${VERSION}"
    DESCRIPTION "A Zephir compiler")

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# CMake Script Includes
include(build-types)
include(compiler-detect)
include(c++-standards)
include(compiler-options)
include(code-coverage)

# Require C++17
cxx_17()

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}"
      CACHE STRING "Directory to install zephir to" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if(CODE_COVERAGE)
    add_code_coverage_all_targets(EXCLUDE
        /usr/*
        '.*\.test\..*'
        .*/test/.*
        .*/tests/.*
        .*/external/.*
        *test*)
endif()

add_subdirectory(external)
add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

option(ZEPHIR_BUILD_TESTING "Build test project" OFF)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING AND ZEPHIR_BUILD_TESTING)
    include(cppcheck)

    message(STATUS "Include test sources")
    add_subdirectory(tests)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
