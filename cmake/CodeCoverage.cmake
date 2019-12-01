# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

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
    GCOV_EXECUTABLE
    NAMES gcov
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)

  find_program(
    LCOV_EXECUTABLE
    NAMES lcov lcov.perl
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)

  find_program(
    GENHTML_EXECUTABLE
    NAMES genhtml genhtml.perl
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)

  find_program(
    GCOVR_EXECUTABLE
    NAMES gcovr
    PATHS /usr/local /usr
    PATH_SUFFIXES bin)
elseif(WIN32)
  find_program(
    GCOV_EXECUTABLE
    NAMES gcov.exe gcov.bat
    PATHS C:/
    PATH_SUFFIXES "")

  find_program(
    LCOV_EXECUTABLE
    NAMES lcov.exe lcov.bat lcov.perl
    PATHS C:/
    PATH_SUFFIXES "")

  find_program(
    GENHTML_EXECUTABLE
    NAMES genhtml.exe genhtml.bat genhtml.perl
    PATHS C:/
    PATH_SUFFIXES "")

  find_program(
    GCOVR_EXECUTABLE
    NAMES gcovr.exe
    PATHS C:/
    PATH_SUFFIXES "")
endif()

mark_as_advanced(GCOV_EXECUTABLE LCOV_EXECUTABLE GENHTML_EXECUTABLE
                 GCOVR_EXECUTABLE)

# Variables
set(CCOV_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ccov)

function(setup_code_coverage_target)
  # Define the supported set of keywords
  set(prefix ARG)
  set(noValues NONE)
  set(singleValues NAME)
  set(multiValues EXECUTABLE EXECUTABLE_ARGS DEPENDENCIES LCOV_ARGS
                  GENHTML_ARGS)

  # Process the arguments passed in
  include(CMakeParseArguments)

  cmake_parse_arguments(${prefix} "${noValues}" "${singleValues}"
                        "${multiValues}" ${ARGN})

  assert_compiler_supported()
  ensure_built_type()

  if(NOT LCOV_EXECUTABLE)
    message(FATAL_ERROR "lcov not found! Aborting...")
  endif()

  if(NOT GCOV_EXECUTABLE)
    message(FATAL_ERROR "gcov not found! Aborting...")
  endif()

  if(NOT GENHTML_EXECUTABLE)
    message(FATAL_ERROR "genhtml not found! Aborting...")
  endif()

  # Setup targets

  add_custom_target(
    ccov-clean
    COMMAND ${CMAKE_COMMAND} -E remove ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.base
            ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.total
            ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.clean
    COMMAND
      ${LCOV_EXECUTABLE} ${ARG_LCOV_ARGS} --gcov-tool ${GCOV_EXECUTABLE}
      --directory ${CMAKE_BINARY_DIR} --zerocounters
    COMMENT "Reset all execution counts to zero")

  add_custom_target(
    ccov-preprocessing
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCOV_OUTPUT_DIRECTORY}
    DEPENDS ccov-clean
    COMMENT "Create directory to collect coverage data")

  add_custom_target(
    ccov-init
    COMMAND
      ${LCOV_EXECUTABLE} ${ARG_LCOV_ARGS} --gcov-tool ${GCOV_EXECUTABLE}
      --capture --initial --directory ${CMAKE_BINARY_DIR} --output-file
      ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.base
    DEPENDS ccov-preprocessing
    COMMENT "Create baseline to make sure untouched files show up in the report"
  )

  add_custom_target(
    ${ARG_NAME}
    COMMAND ${ARG_EXECUTABLE} ${ARG_EXECUTABLE_ARGS}
    COMMAND
      ${LCOV_EXECUTABLE} ${ARG_LCOV_ARGS} --gcov-tool ${GCOV_EXECUTABLE}
      --directory ${CMAKE_BINARY_DIR} --capture --output-file
      ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.info
    COMMAND
      ${LCOV_EXECUTABLE} ${ARG_EXECUTABLE_ARGS} --gcov-tool ${GCOV_EXECUTABLE}
      --add-tracefile ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.base --add-tracefile
      ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.info --output-file
      ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.total
    COMMAND
      ${LCOV_EXECUTABLE} ${ARG_EXECUTABLE_ARGS} --gcov-tool ${GCOV_EXECUTABLE}
      --remove ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.total ${COVERAGE_EXCLUDES}
      --output-file ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.clean
    COMMAND ${GENHTML_EXECUTABLE} ${ARG_GENHTML_ARGS} --output-directory
            ${CCOV_OUTPUT_DIRECTORY} ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.clean
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ccov-init ${ARG_DEPENDENCIES}
    COMMENT
      "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
  )

  add_custom_command(
    TARGET ${ARG_NAME} POST_BUILD
    COMMAND ;
    COMMENT "Lcov code coverage info report saved in ${ARG_NAME}.info")

  add_custom_target(
    ccov-html
    COMMAND ${GENHTML_EXECUTABLE} ${ARG_GENHTML_ARGS} --output-directory
            ${CCOV_OUTPUT_DIRECTORY} ${CCOV_OUTPUT_DIRECTORY}/${ARG_NAME}.clean
    COMMENT "Generating HTML coverage report")

  add_custom_command(
    TARGET ccov-html POST_BUILD
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
