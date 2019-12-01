# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

option(CPPCHECK "Turns on cppcheck processing if it is found." OFF)

# Adds cppcheck to the compilation, with the given arguments being used as the
# options set.

if(UNIX)
  find_program(
    CPPCHECK_BIN
    NAMES cppcheck
    PATHS /usr /usr/local /opt /opt/local
    PATH_SUFFIXES bin)
elseif(WIN32)
  find_program(
    CPPCHECK_BIN
    NAMES cppcheck.exe
    PATHS C:/
    PATH_SUFFIXES "")
endif()

mark_as_advanced(CPPCHECK_BIN)

set(_base_message "Check for cppcheck")
if(CPPCHECK_BIN)
  # Version number checking for '-std=c++17' compatibility
  execute_process(
    COMMAND ${CPPCHECK_BIN} --version
    OUTPUT_VARIABLE CPPCHECK_VERSION_CALL_OUTPUT
    RESULT_VARIABLE CPPCHECK_VERSION_RESULT
    ERROR_VARIABLE CPPCHECK_VERSION_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(CPPCHECK_VERSION_RESULT)
    string(CONCAT CPPCHECK_FIND_ERROR
                  "Command \"${CPPCHECK_BIN} --version\" failed "
                  "with output:\n${CPPCHECK_VERSION_ERROR}")

    message(FATAL_ERROR "${CPPCHECK_FIND_ERROR}")
  endif()

  string(REGEX MATCH "[0-9]+\\.[0-9]+" CPPCHECK_VERSION
               ${CPPCHECK_VERSION_CALL_OUTPUT})

  if(CPPCHECK_VERSION VERSION_LESS "1.89")
    message(
      SEND_ERROR
        "Cppcheck ${CPPCHECK_VERSION} require option --std=c++17 which is available on cppcheck >= 1.89"
    )
  endif()

  message(STATUS "${_base_message}: ${CPPCHECK_BIN}")
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        "${CPPCHECK_BIN}"
        "--enable=warning,performance,portability,missingInclude"
        "--language=c++"
        "--std=c++17"
        "--template={file}:{line}:{column}:\ {severity}:\ {message}\ [--suppress={id}]\\n{code}"
        "--inline-suppr"
        "--suppressions-list=${CMAKE_SOURCE_DIR}/cpppcheck.supp"
        "-j${BUILD_JOBS}"
        "--quiet"
        "--verbose"
        "--force")
  endif()

elseif(CPPCHECK)
  message(SEND_ERROR "${_base_message}: executable not found!")
  set(CMAKE_CXX_CPPCHECK
      ""
      CACHE STRING "" FORCE) # delete it
else()
  message(STATUS "${_base_message}: not found")
  set(CMAKE_CXX_CPPCHECK
      ""
      CACHE STRING "" FORCE) # delete it
endif()

# cppcheck.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
