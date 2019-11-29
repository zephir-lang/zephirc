# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# A module to find SpdLog library.
#
# By default, the dynamic libraries of spdlog will be found. To find the static
# ones instead, you must set the SPDLOG_STATIC_LIBRARY variable to TRUE before
# calling find_package(SPDLOG ...).
#
# Example:
# ~~~
# set(SPDLOG_STATIC_LIBRARY TRUE)
# find_package(SPDLOG REQUIRED)
# ~~~
#
# If spdlog is not installed in a standard path, you can use the SPDLOG_DIR
# CMake variable to tell CMake where spdlog is.
#
# The module defines the following variables:
#
# * SPDLOG_FOUND:       if false, do not try to link to spdlog
# * SPDLOG_LIBRARY:     where to find spdlog
# * SPDLOG_INCLUDE_DIR: where to find spdlog/spdlog.h

# Attempt to find static library first if this is set
if(SPDLOG_STATIC_LIBRARY)
  if(UNIX)
    set(SPDLOG_STATIC libspdlog.a)
  elseif(WIN32)
    set(SPDLOG_STATIC spdlog.lib)
  endif()
endif()

if(UNIX)
  # find spdlog include directory
  find_path(
    SPDLOG_INCLUDE_DIR spdlog/spdlog.h
    PATHS ${SPDLOG_DIR} /usr /usr/local /opt /opt/local
    PATH_SUFFIXES include)

  # find spdlog pre-compiled library
  find_library(
    SPDLOG_LIBRARY
    NAMES ${SPDLOG_STATIC} spdlog
    PATHS ${SPDLOG_DIR} /usr /usr/local /opt /opt/local
    PATH_SUFFIXES lib64 lib)
elseif(WIN32)
  # find spdlog include directory
  find_path(
    SPDLOG_INCLUDE_DIR spdlog/spdlog.h
    PATHS ${SPDLOG_DIR} C:/
    PATH_SUFFIXES include)

  # find spdlog pre-compiled library
  find_library(
    SPDLOG_LIBRARY
    NAMES ${SPDLOG_STATIC} spdlog
    PATHS ${SPDLOG_DIR} C:/
    PATH_SUFFIXES lib64 lib)
endif()

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if
# all listed variables are TRUE
find_package_handle_standard_args(
        ${CMAKE_FIND_PACKAGE_NAME} REQUIRED_VARS SPDLOG_INCLUDE_DIR SPDLOG_LIBRARY)

mark_as_advanced(SPDLOG_INCLUDE_DIR SPDLOG_LIBRARY)

# FindSPDLOG.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
