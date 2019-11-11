# FindYamlCpp.cmake
#
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
#
# YAMLCPP_FOUND       - if false, do not try to link to yaml-cpp
# YAMLCPP_LIBRARY     - where to find yaml-cpp
# YAMLCPP_INCLUDE_DIR - where to find yaml.h

# Attempt to find static library first if this is set
if(YAMLCPP_STATIC_LIBRARY)
  set(YAMLCPP_STATIC libyaml-cpp.a)
endif()

if(UNIX)
  # find the yaml-cpp include directory
  find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
            PATHS /usr
                  /usr/local
                  /opt
                  /opt/local
                  ${YAMLCPP_DIR}/include
            PATH_SUFFIXES include)

  # find the yaml-cpp library
  find_library(YAMLCPP_LIBRARY
               NAMES ${YAMLCPP_STATIC} yaml-cpp
               PATHS /usr
                     /usr/local
                     /opt
                     /opt/local
                     ${YAMLCPP_DIR}/lib
               PATH_SUFFIXES lib64 lib)
elseif(WIN32)
  # find the yaml-cpp include directory
  find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h
            PATHS /usr
                  /usr/local
                  /opt
                  /opt/local
                  ${YAMLCPP_DIR}/include
            PATH_SUFFIXES include)

  # find the yaml-cpp library
  find_library(YAMLCPP_LIBRARY
               NAMES ${YAMLCPP_STATIC} yaml-cpp
               PATHS /usr
                     /usr/local
                     /opt
                     /opt/local
                     ${YAMLCPP_DIR}/lib
               PATH_SUFFIXES lib64 lib)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
                                  REQUIRED_VARS
                                  YAMLCPP_INCLUDE_DIR
                                  YAMLCPP_LIBRARY)

mark_as_advanced(YAMLCPP_INCLUDE_DIR)
mark_as_advanced(YAMLCPP_LIBRARY)

if(NOT ${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
  if(YAMLCPP_FOUND)
    message(STATUS "Check for yaml-cpp: ${YAMLCPP_LIBRARY}")
  else()
    message(STATUS "Check for yaml-cpp: not found")
  endif()
endif()
