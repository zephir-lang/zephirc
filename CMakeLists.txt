# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

cmake_minimum_required(VERSION 3.11...3.16)

# Prepare VERSION variable
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.cmake)

project(
  zephir
  LANGUAGES CXX
  VERSION ${ZEPHIR_VERSION}
  DESCRIPTION "A Zephir compiler")

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${zephir_SOURCE_DIR}/cmake)

# Options
option(CODE_COVERAGE "Builds targets with code coverage instrumentation." OFF)
option(ZEPHIR_BUILD_TESTING "Build test project" OFF)

# CMake Script Includes
include(Bootstrap)
include(Cppcheck)

if(NOT EXISTS "${zephir_SOURCE_DIR}/external/cmake-scripts/c++-standards.cmake")
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
      "Failed to get required git modules: ${output}"
      "  Result: ${result}\n"
      "  Output:\n"
      "    ${output}\n")
    # cmake-format: on
  endif()

  unset(result)
  unset(output)
endif()
list(APPEND CMAKE_MODULE_PATH ${zephir_SOURCE_DIR}/external/cmake-scripts)

# TODO(klay): Remove symlinks after this https://github.com/StableCoder/cmake-
# scripts/pull/10
include(formatting)
include(c++-standards)
include(compiler-options)
include(code-coverage)

# Require C++17
cxx_17()

# Tools
file(
  GLOB_RECURSE
    ZEPHIR_SOURCE_FILES
    ${zephir_SOURCE_DIR}/include/*.[hc]
    ${zephir_SOURCE_DIR}/include/*.[hc]pp
    ${zephir_SOURCE_DIR}/src/*.[hc]
    ${zephir_SOURCE_DIR}/src/*.[hc]pp
    ${zephir_SOURCE_DIR}/tests/*.[hc]
    ${zephir_SOURCE_DIR}/tests/*.[hc]pp)
clang_format(cpp-format ${ZEPHIR_SOURCE_FILES})

file(
  GLOB_RECURSE
    ZEPHIR_CMAKE_FILES ${zephir_SOURCE_DIR}/cmake/*.cmake
    ${zephir_SOURCE_DIR}/src/*.cmake ${zephir_SOURCE_DIR}/tests/*.cmake
    ${zephir_SOURCE_DIR}/CMakeLists.txt)
cmake_format(cmake-format ${ZEPHIR_CMAKE_FILES})

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_BINARY_DIR}"
      CACHE STRING "Directory to install zephir to" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Handle codecoverage
if(CODE_COVERAGE)
  # Now we can exclude the stuff that we aren't interested in from the
  # tracefile:
  #
  # * system deps
  # * tests
  # * build
  # * thridparty-code
  set(COVERAGE_EXCLUDES
      "/usr/*"
      "build/*"
      "*/build/*"
      "tests/*"
      "*/tests/*"
      "external/*"
      "*/external/*")

  # This introduces the 'ccov-all' targets
  add_code_coverage_all_targets(EXCLUDE ${COVERAGE_EXCLUDES})
endif()

# Conan bootstrap
#
# Assumptions:
#
# * The file conanfile.txt is in this directory
# * This CMakeLists.txt file is in the project ROOT directory
# * The conan application is the project $PATH environment variable and
#   accessible from command line
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  execute_process(
    COMMAND conan install . #
            --install-folder "${CMAKE_BINARY_DIR}" #
            --build=missing
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    RESULT_VARIABLE result
    OUTPUT_VARIABLE output
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(result)
    message(FATAL_ERROR "Failed to get required libraries: ${output}")
  endif()

  unset(result)
  unset(output)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

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
