# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# TODO(klay): Refacor me.

# If cppcheck is installed, create a target to run it on the project source
# files.
if(UNIX)
  find_program(
    CPPCHECK_EXECUTABLE
    NAMES cppcheck
    PATHS $ENV{CPPCHECK_DIR} /usr /usr/local /opt /opt/local
    PATH_SUFFIXES bin)
elseif(WIN32)
  find_program(
    CPPCHECK_EXECUTABLE
    NAMES cppcheck.exe
    PATHS $ENV{CPPCHECK_DIR} C:/
    PATH_SUFFIXES "")
endif()

mark_as_advanced(CPPCHECK_EXECUTABLE)

if(CPPCHECK_EXECUTABLE)
  message(STATUS "Check for cppcheck: ${CPPCHECK_EXECUTABLE}")
  add_custom_target(
    cppcheck
    COMMAND
      "${CPPCHECK_EXECUTABLE}" --quiet --error-exitcode=1
      --enable=warning,portability,performance,style --language=c++
      "--std=c++${CMAKE_CXX_STANDARD}"
      "--suppress=*:${CMAKE_SOURCE_DIR}/src/commands/options.cpp"
      "${CMAKE_SOURCE_DIR}/src")
else()
  message(STATUS "Check for cppcheck: not found")
endif()

# cppcheck.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
