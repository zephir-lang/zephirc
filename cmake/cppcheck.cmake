# cmake-format: off
#
# Copyright (C) 2018 by George Cave - gcave@stablecoder.ca
# Copyright (C) 2019 by Zephir Team - <team@zephir-lang.com>
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
# cmake-format: on

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
        "--suppress=missingIncludeSystem"
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
