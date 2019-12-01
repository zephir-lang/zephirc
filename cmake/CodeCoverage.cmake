# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Common checks to not run twice
if(CCOV_ADDED)
  return()
endif()

set(CCOV_ADDED ON)

# Check compiler support
macro(assert_compiler_supported)
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|(Apple)?[Cc]lang")
    message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting...")
    return()
  endif()

  if(CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3)
      message(FATAL_ERROR "Clang version must be 3.0.0 or greater! Aborting...")
    endif()
  endif()
endmacro()

# Check build type
macro(ensure_built_type)
  set(ccovWarn
      "Code coverage results with an optimised build may be misleading")

  if(CMAKE_BUILD_TYPE)
    string(TOUPPER ${CMAKE_BUILD_TYPE} upperBuildType)
    if(NOT ${upper_build_type} STREQUAL "DEBUG")
      message(WARNING "${ccovWarn}")
    endif()
    unset(upperBuildType)
  elseif()
    message(WARNING "${ccovWarn}")
  endif()

  unset(ccovWarn)
endmacro()

# Check prerequisites
if(UNIX)
  find_program(
    LCOV_EXE
    NAMES lcov lcov.perl
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)

  find_program(
    GENHTML_EXE
    NAMES genhtml genhtml.perl
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)

  find_program(
    GCOVR_EXE
    NAMES gcovr
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)
elseif(WIN32)
  find_program(
    LCOV_EXE
    NAMES lcov.exe lcov.bat lcov.perl
    PATHS C:/
    PATH_SUFFIXES "")

  find_program(
    GENHTML_EXE
    NAMES genhtml.exe genhtml.bat genhtml.perl
    PATHS C:/
    PATH_SUFFIXES "")

  find_program(
    GCOVR_EXE
    NAMES gcovr.exe
    PATHS C:/
    PATH_SUFFIXES "")
endif()

mark_as_advanced(LCOV_EXE GENHTML_EXE GCOVR_EXE CCOV_ADDED)

if(NOT LCOV_EXE)
  message(FATAL_ERROR "lcov not found! Aborting...")
endif()

# Variables
set(CCOV_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ccov)

add_custom_target(
  coverage-preprocessing
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CCOV_OUTPUT_DIRECTORY}
  DEPENDS coverage-clean
  COMMENT "Create directory to collect coverage data")

add_custom_target(
  coverage-clean
  COMMAND ${LCOV_EXE} --directory ${CMAKE_BINARY_DIR} --zerocounters
  COMMENT "Resetting code coverage counters to zero")

function(setup_code_coverage_target)
  # Define the supported set of keywords
  set(prefix ARG)
  set(noValues NONE)
  set(singleValues NAME)
  set(multiValues EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES LCOV_ARGS
                  GENHTML_ARGS)

  # Process the arguments passed in
  cmake_parse_arguments(${prefix} "${noValues}" "${singleValues}"
                        "${multiValues}" ${ARGN})

  assert_compiler_supported()
  ensure_built_type()

  if(NOT GENHTML_EXE)
    message(FATAL_ERROR "genhtml not found! Aborting...")
  endif()

  set(COVERAGE_INFO "${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.info")

  # Setup targets

  add_custom_target(
    coverage-init
    COMMAND
      ${LCOV_EXE} ${ARG_LCOV_ARGS} --capture --initial #
      --directory ${CMAKE_BINARY_DIR} #
      --output-file ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.base 2> /dev/null
    DEPENDS coverage-preprocessing
    COMMENT "Capture base info")

  add_custom_target(
    ${ARG_NAME}
    COMMAND ${CMAKE_COMMAND} -E remove ${COVERAGE_INFO}
    COMMAND ${ARG_EXECUTABLE} ${ARG_EXECUTABLE_ARGS}
    COMMAND
      ${LCOV_EXE} ${ARG_LCOV_ARGS} --directory ${CMAKE_BINARY_DIR} --capture #
      --output-file ${COVERAGE_INFO} 2> /dev/null
    COMMAND
      ${LCOV_EXE} ${ARG_LCOV_ARGS} #
      --add-tracefile ${COVERAGE_INFO} #
      --add-tracefile ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.base #
      --output-file ${COVERAGE_INFO} #
    COMMAND
      ${LCOV_EXE} ${ARG_LCOV_ARGS} --remove ${COVERAGE_INFO}
      ${COVERAGE_EXCLUDES} --output-file ${COVERAGE_INFO}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS coverage-init ${ARG_DEPENDENCIES}
    COMMENT "Processing code coverage counters and generating report.")

  add_custom_command(
    TARGET ${ARG_NAME} POST_BUILD
    COMMAND ;
    COMMENT "Lcov code coverage info report saved in ${COVERAGE_INFO}")

  add_custom_target(
    coverage-html
    COMMAND ${GENHTML_EXE} ${ARG_GENHTML_ARGS} #
            --output-directory ${CCOV_OUTPUT_DIRECTORY} ${COVERAGE_INFO}
    COMMENT "Generating HTML coverage report")

  add_custom_command(
    TARGET coverage-html POST_BUILD
    COMMAND ;
    COMMENT
      "Open ${CCOV_OUTPUT_DIRECTORY}/index.html in your browser to view the coverage report."
  )
endfunction()

# CodeCoverage.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
