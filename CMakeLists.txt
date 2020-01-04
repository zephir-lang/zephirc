# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

cmake_minimum_required(VERSION 3.11...3.16)

project(zephir LANGUAGES CXX)

# See: https://github.com/conan-io/cmake-conan/issues/159
cmake_policy(SET CMP0025 NEW)

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${zephir_SOURCE_DIR}/cmake)

# Determine if zephir is built as a subproject (using add_subdirectory) or if it
# is the master project.
set(MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MASTER_PROJECT ON)
  message(STATUS "CMake version: ${CMAKE_VERSION}")
endif()

# CMake Script Includes
include(Bootstrap)
include(Helpers)
include(Cppcheck)
include(CodeCoverage)

if(NOT EXISTS "${zephir_SOURCE_DIR}/external/cmake-scripts/c++-standards.cmake"
   OR NOT EXISTS "${zephir_SOURCE_DIR}/tests/sharness/sharness.sh")
  # Here, it provides the GIT_EXECUTABLE variable after searching for the git
  # binary in some standard/well-known locations for the current platform.
  find_package(Git REQUIRED)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(NOT ${result} EQUAL 0)
    string(REPLACE "\n" "\n    " output "${output}")
    # cmake-format: off
    message(FATAL_ERROR
      "Failed to get required git modules.\n"
      "  Result: ${result}\n"
      "  Output:\n"
      "    ${output}\n")
    # cmake-format: on
  endif()

  unset(result)
  unset(output)
endif()
list(APPEND CMAKE_MODULE_PATH ${zephir_SOURCE_DIR}/external/cmake-scripts)

include(formatting)
include(c++-standards)
include(compiler-options)
include(dependency-graph)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Builds a dependency graph
gen_dep_graph(png)

# Tools
file(
  GLOB_RECURSE
  glob_files
  ${zephir_SOURCE_DIR}/include/*.[hc]
  ${zephir_SOURCE_DIR}/include/*.[hc]pp
  ${zephir_SOURCE_DIR}/src/*.[hc]
  ${zephir_SOURCE_DIR}/src/*.[hc]pp
  ${zephir_SOURCE_DIR}/tests/*.[hc]
  ${zephir_SOURCE_DIR}/tests/*.[hc]pp)
clang_format(cpp-format ${glob_files})

file(GLOB_RECURSE glob_files "${zephir_SOURCE_DIR}/cmake/*.cmake"
     "${zephir_SOURCE_DIR}/src/CMakeLists.txt")
list(
  APPEND glob_files
         ${zephir_SOURCE_DIR}/CMakeLists.txt
         ${zephir_SOURCE_DIR}/docs/CMakeLists.txt
         ${zephir_SOURCE_DIR}/src/CMakeLists.txt
         ${zephir_SOURCE_DIR}/share/CMakeLists.txt
         ${zephir_SOURCE_DIR}/tests/CMakeLists.txt
         ${zephir_SOURCE_DIR}/external/CMakeLists.txt)
cmake_format(cmake-format "${glob_files}")

# Conan helpers
include(ConanHelper)

# Project specific variables
include(ProjectInfo)

# Project specific directories
include(ProjectDirs)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(share)

option(ZEPHIR_BUILD_TESTING "Build test project" OFF)
if(MASTER_PROJECT)
  add_subdirectory(docs)
  include(CTest)

  if(BUILD_TESTING AND ZEPHIR_BUILD_TESTING)
    add_subdirectory(tests)
  endif()
endif()

# Evaluate coverage
coverage_evaluate()
