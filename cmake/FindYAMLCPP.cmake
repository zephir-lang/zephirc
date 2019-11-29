# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# A module to find yaml-cpp module.
#
# By default, the dynamic libraries of yaml-cpp will be found. To find the
# static ones instead, you must set the YAMLCPP_STATIC_LIBRARY variable to TRUE
# before calling find_package(YAMLCPP ...).
#
# Example:
# ~~~
# set(YAMLCPP_STATIC_LIBRARY TRUE)
# find_package(YAMLCPP REQUIRED)
# ~~~
#
# If yaml-cpp is not installed in a standard path, you can use the YAMLCPP_DIR
# CMake variable to tell CMake where yaml-cpp is.
#
# The module defines the following variables:
#
# * YAMLCPP_FOUND:       If false, do not try to link to yaml-cpp
# * YAMLCPP_LIBRARY:     Where to find yaml-cpp
# * YAMLCPP_INCLUDE_DIR: Where to find yaml.h

# Attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
  if(UNIX)
    set(YAMLCPP_STATIC libyaml-cpp.a)
  else()
    set(YAMLCPP_STATIC yaml-cpp.lib)
  endif()
endif()

unset(YAMLCPP_INCLUDE_DIR CACHE)
unset(YAMLCPP_LIBRARY CACHE)

if(UNIX)
  # find the yaml-cpp include directory
  find_path(
    YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
    PATHS ${YAMLCPP_DIR} /usr /usr/local /opt /opt/local
    PATH_SUFFIXES include)

  # find the yaml-cpp library
  find_library(
    YAMLCPP_LIBRARY
    NAMES ${YAMLCPP_STATIC} yaml-cpp
    PATHS ${YAMLCPP_DIR} /usr /usr/local /opt /opt/local
    PATH_SUFFIXES lib64 lib)
elseif(WIN32)
  # find the yaml-cpp include directory
  find_path(
    YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
    PATHS ${YAMLCPP_DIR} C:/
    PATH_SUFFIXES include)

  # find the yaml-cpp library
  find_library(
    YAMLCPP_LIBRARY
    NAMES ${YAMLCPP_STATIC} yaml-cpp
    PATHS ${YAMLCPP_DIR} C:/
    PATH_SUFFIXES lib64 lib)
endif()

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set YAMLCPP_FOUND to TRUE if all
# listed variables are TRUE
find_package_handle_standard_args(
  ${CMAKE_FIND_PACKAGE_NAME} REQUIRED_VARS YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)

mark_as_advanced(YAMLCPP_INCLUDE_DIR YAMLCPP_LIBRARY)

# FindYAMLCPP.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
