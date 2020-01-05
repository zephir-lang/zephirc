# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>

# NOTE: CODE COVERAGE DOES NOT WORK RUNNING IN PARALLEL:
# https://github.com/linux-test-project/lcov/issues/37

# Adds an option to choose, if coverage should be enabled or not. If enabled
# marked targets will be build with coverage support and appropriate targets
# will be added. If disabled coverage will be ignored for all targets.
option(CODE_COVERAGE "Builds targets with code coverage instrumentation." OFF)

set(COVERAGE_FLAG_CANDIDATES
    # gcc and clang
    "-fprofile-arcs -ftest-coverage"
    # gcc and clang fallback
    "--coverage")

# Adds coverage support for target <TARGET_NAME> and register target for
# coverage evaluation. If coverage is disabled or not supported, this function
# will simply do nothing.
#
# ~~~
# Note: This function is only a wrapper to define this function always, even if
#   coverage is not supported by the compiler or disabled. This function must
#   be defined here, because the module will be exited, if there is no coverage
#   support by the compiler or it is disabled by the user.
#
# Required:
# TARGET_NAME - The target name add coverage support to.
# ~~~
function(code_coverage TARGET_NAME)
  # Only add coverage for target, if coverage is support and enabled.
  if(CODE_COVERAGE)
    foreach(TARGET_NAME ${ARGV})
      target_code_coverage(${TARGET_NAME})
    endforeach()
  endif()
endfunction()

# Adds global target to gather coverage information after all targets have been
# added. Other evaluation functions could be added here, after checks for the
# specific module have been passed.
#
# ~~~
# Note: This function is only a wrapper to define this function always, even if
#   coverage is not supported by the compiler or disabled. This function must
#   be defined here, because the module will be exited, if there is no coverage
#   support by the compiler or it is disabled by the user.
# ~~~
function(coverage_collect)
  # add lcov evaluation
  if(LCOV_FOUND)
    lcov_capture_initial()
    lcov_capture()
  endif()
endfunction()

# Exit this module, if coverage is disabled. code_coverage is defined before
# this return, so this module can be exited now safely without breaking any
# build- scripts.
if(NOT CODE_COVERAGE)
  return()
endif()

if(CMAKE_BUILD_TYPE)
  string(TOUPPER ${CMAKE_BUILD_TYPE} upper_build_type)
  if(NOT ${upper_build_type} STREQUAL "DEBUG")
    message(
      WARNING "Code coverage results with an optimized build may be misleading")
  endif()
else()
  message(
    WARNING "Code coverage results with an optimized build may be misleading")
endif()

get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
foreach(LANG ${ENABLED_LANGUAGES})
  # Coverage flags are not dependent on language, but the used compiler. So
  # instead of searching flags foreach language, search flags foreach compiler
  # used.
  set(COMPILER ${CMAKE_${LANG}_COMPILER_ID})

  if(NOT COVERAGE_${COMPILER}_FLAGS)
    foreach(FLAG ${COVERAGE_FLAG_CANDIDATES})
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Try ${COMPILER} code coverage flags: ${FLAG}")
      endif()

      set(CMAKE_REQUIRED_FLAGS "${FLAG}")
      unset(COVERAGE_FLAG_DETECTED CACHE)

      if(${LANG} STREQUAL "C")
        include(CheckCCompilerFlag)
        check_c_compiler_flag("${FLAG}" COVERAGE_FLAG_DETECTED)
      elseif(${LANG} STREQUAL "CXX")
        include(CheckCXXCompilerFlag)
        check_cxx_compiler_flag("${FLAG}" COVERAGE_FLAG_DETECTED)
      endif()

      if(COVERAGE_FLAG_DETECTED)
        set(COVERAGE_${COMPILER}_FLAGS
            "${FLAG}"
            CACHE STRING "${COMPILER} flags for code coverage.")
        mark_as_advanced(COVERAGE_${COMPILER}_FLAGS)
        break()
      else()
        message(WARNING "Code coverage is not available for ${COMPILER}"
                        " compiler. Targets using this compiler will be "
                        "compiled without it.")
      endif()
    endforeach()
  endif()
endforeach()

# Adds coverage support for target <TARGET_NAME> and register target for
# coverage evaluation.
#
# ~~~
# Required:
# TARGET_NAME - The target name add coverage support to.
# ~~~
function(target_code_coverage TARGET_NAME)
  # Check if all sources for target use the same compiler. If a target uses e.g.
  # C and another language mixed and uses different compilers (e.g. clang and
  # some-compiler) this can trigger huge problems, because different compilers
  # may use different implementations for code coverage.
  get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)

  set(TARGET_COMPILER "")
  set(ADDITIONAL_FILES "")

  foreach(FILE ${TARGET_SOURCES})
    # If expression was found, FILE is a generator-expression for an object
    # library. Object libraries will be ignored.
    string(REGEX MATCH "TARGET_OBJECTS:([^ >]+)" _file ${FILE})
    if("${_file}" STREQUAL "")
      detect_language(${FILE} LANG)
      if(LANG)
        list(APPEND TARGET_COMPILER ${CMAKE_${LANG}_COMPILER_ID})

        list(APPEND ADDITIONAL_FILES "${FILE}.gcno")
        list(APPEND ADDITIONAL_FILES "${FILE}.gcda")
      endif()
    endif()
  endforeach()

  list(REMOVE_DUPLICATES TARGET_COMPILER)
  list(LENGTH TARGET_COMPILER NUM_COMPILERS)

  if(NUM_COMPILERS GREATER 1)
    message(
      WARNING "Can't use code coverage for target ${TARGET_NAME}, because "
              "it will be compiled by incompatible compilers. Target will be "
              "compiled without code coverage.")
    return()

  elseif(NUM_COMPILERS EQUAL 0)
    message(
      WARNING "Can't use code coverage for target ${TARGET_NAME}, because "
              "it uses an unknown compiler. Target will be compiled without "
              "code coverage.")
    return()

  elseif(NOT DEFINED "COVERAGE_${TARGET_COMPILER}_FLAGS")
    # A warning has been printed before, so just return if flags for this
    # compiler aren't available.
    return()
  endif()

  # enable coverage for target
  set_property(
    TARGET ${TARGET_NAME}
    APPEND_STRING
    PROPERTY COMPILE_FLAGS " ${COVERAGE_${TARGET_COMPILER}_FLAGS}")
  set_property(
    TARGET ${TARGET_NAME}
    APPEND_STRING
    PROPERTY LINK_FLAGS " ${COVERAGE_${TARGET_COMPILER}_FLAGS}")

  # Adds gcov files generated by compiler to clean target.
  set(CLEAN_FILES "")
  foreach(FILE ${ADDITIONAL_FILES})
    relative_path(${FILE} FILE)
    list(APPEND CLEAN_FILES "CMakeFiles/${TARGET_NAME}.dir/${FILE}")
  endforeach()

  set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
                                      "${CLEAN_FILES}")

  add_gcov_target(${TARGET_NAME})
  add_lcov_target(${TARGET_NAME})
endfunction()

# Include modules for parsing the collected data and output it in a readable
# format (like gcov and lcov).
find_package(Gcov)
find_package(Lcov)
