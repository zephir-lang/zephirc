# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

option(CPPCHECK "Turns on cppcheck processing if it is found." OFF)

# Adds cppcheck to the compilation, with the given arguments being used as the
# options set.

if(UNIX)
  find_program(
    CPPCHECK_EXE
    NAMES cppcheck
    PATHS /usr /usr/local /opt /opt/local
    PATH_SUFFIXES bin)
elseif(WIN32)
  find_program(
    CPPCHECK_EXE
    NAMES cppcheck.exe
    PATHS C:/
    PATH_SUFFIXES "")
endif()

mark_as_advanced(CPPCHECK_EXE)
set(_base_message "Check for cppcheck")
if(CPPCHECK_EXE)
  message(STATUS "${_base_message}: ${CPPCHECK_EXE}")
  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
        "${CPPCHECK_EXE}"
        "--enable=warning,performance,portability,missingInclude"
        "--language=c++"
        "--std=c++${CMAKE_CXX_STANDARD}"
        "--template='{file}:{line}:{column} {severity}: {message} [{id}]'"
        "--inline-suppr"
        "--suppressions-list=${CMAKE_SOURCE_DIR}/cpppcheck.supp"
        "-j${BUILD_JOBS}"
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
