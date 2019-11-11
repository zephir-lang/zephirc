# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# Attempt to find static library first if this is set
if(SPDLOG_STATIC_LIBRARY)
  if(UNIX)
    set(SPDLOG_STATIC libspdlog.a)
  elseif(WIN32)
    set(SPDLOG_STATIC libspdlog.lib)
  endif()
endif()

if(UNIX)
  # find spdlog include directory
  find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h
    PATHS /usr
          /usr/local
          /opt
          /opt/local
          ${SPDLOG_DIR}/include
    PATH_SUFFIXES include
    DOC "path to spdlog include directory")

  # find spdlog pre-compiled library
  find_library(SPDLOG_LIBRARY
    NAMES ${SPDLOG_STATIC} libspdlog
    PATHS /usr
          /usr/local
          /opt
          /opt/local
          ${SPDLOG_DIR}
    PATH_SUFFIXES lib64 lib
    DOC "path to spdlog pre-compiled library")
elseif(WIN32)
  # find spdlog include directory
  find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h
    PATHS C:/
          ${SPDLOG_DIR}/include
    PATH_SUFFIXES include
    DOC "path to spdlog include directory")

  # find spdlog pre-compiled library
  find_library(SPDLOG_LIBRARY
    NAMES ${SPDLOG_STATIC} libspdlog
    PATHS C:/
          ${SPDLOG_DIR}
    PATH_SUFFIXES lib64 lib
    DOC "path to spdlog pre-compiled library")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
                                  REQUIRED_VARS
                                  SPDLOG_INCLUDE_DIR
                                  SPDLOG_LIBRARY)

mark_as_advanced(SPDLOG_INCLUDE_DIR)
mark_as_advanced(SPDLOG_LIBRARY)

if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
  if(SPDLOG_FOUND)
    message(STATUS "Check for spdlog: ${SPDLOG_LIBRARY}")
    message(STATUS "Check for spdlog: ${SPDLOG_INCLUDE_DIR}")
  else()
    message(STATUS "Check for spdlog: not found")
  endif()
endif()

# FindSpdLog.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
