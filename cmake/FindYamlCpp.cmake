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
# before calling find_package(YamlCpp ...).
#
# If yaml-cpp is not installed in a standard path, you can use the YAMLCPP_DIR
# CMake variable to tell CMake where yaml-cpp is.
#
# The module defines the following variables:
# ~~~
# YAMLCPP_FOUND       - if false, do not try to link to yaml-cpp
# YAMLCPP_LIBRARY     - where to find yaml-cpp
# YAMLCPP_INCLUDE_DIR - where to find yaml.h
# ~~~

# Attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
  if(UNIX)
    set(YAMLCPP_STATIC libyaml-cpp.a libyaml.a)
  else()
    set(YAMLCPP_STATIC yaml-cpp.lib)
  endif()
endif()

unset(YAMLCPP_INCLUDE_DIR CACHE)
unset(YAMLCPP_LIBRARY CACHE)

if(UNIX)
  # find the yaml-cpp include directory
  find_path(YAMLCPP_INCLUDE_DIR yaml.h
            PATHS /usr
                  /usr/local
                  /opt
                  /opt/local
                  ${YAMLCPP_DIR}
            PATH_SUFFIXES include/yaml-cpp)

  # find the yaml-cpp library
  find_library(YAMLCPP_LIBRARY
               NAMES ${YAMLCPP_STATIC} yaml-cpp
               PATHS /usr
                     /usr/local
                     /opt
                     /opt/local
                     ${YAMLCPP_DIR}
               PATH_SUFFIXES lib64 lib)
elseif(WIN32)
  # find the yaml-cpp include directory
  find_path(YAMLCPP_INCLUDE_DIR yaml.h
            PATHS C:/ ${YAMLCPP_DIR}
            PATH_SUFFIXES include/yaml-cpp)

  # find the yaml-cpp library
  find_library(YAMLCPP_LIBRARY
               NAMES yaml-cpp yaml-cpp.lib
               PATHS C:/ ${YAMLCPP_DIR}
               PATH_SUFFIXES lib64 lib)
endif()

mark_as_advanced(YAMLCPP_INCLUDE_DIR)
mark_as_advanced(YAMLCPP_LIBRARY)

include(FindPackageHandleStandardArgs)
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED
   AND NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
  find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
                                    REQUIRED_VARS
                                    YAMLCPP_INCLUDE_DIR
                                    YAMLCPP_LIBRARY)
else()
  find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
                                    DEFAULT_MSG
                                    YAMLCPP_INCLUDE_DIR
                                    YAMLCPP_LIBRARY)
endif()

# FindYamlCpp.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
