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

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    string(CONCAT IN_BUILD_ERROR
                  "In-source builds not allowed. Please make a new directory "
                  "(called a build directory) and run CMake from there. "
                  "You may need to remove CMakeCache.txt.")

    message(FATAL_ERROR "${IN_BUILD_ERROR}")
endif()

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(build-types)

include(compiler-detect)
include(c++-standards)
include(compiler-options)
include(code-coverage)

# Require C++11
if(NOT CMAKE_CXX_STANDARD)
    cxx_11()
endif()

if(CMAKE_CXX_STANDARD LESS 11)
    message(WARNING "Incompatible C++ standard ${CMAKE_CXX_STANDARD}. Zephir requires C++11")
endif()

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}"
      CACHE STRING "Directory to install zephir to" FORCE)
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

option(ZEPHIR_BUILD_TESTING "Build test project"           OFF)

if(CODE_COVERAGE)
    add_code_coverage_all_targets(EXCLUDE tests/*)
endif()

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

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
