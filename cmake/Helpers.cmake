# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Get the relative path of the source file destination path.
#
# ~~~
# Required:
# FILE - The source file destination path.
# RESULT_VARIABLE - The result variable.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>
# ~~~
function(relative_path)
  # Define the supported set of keywords
  set(singleValues FILE RESULT_VARIABLE)

  # Process the arguments passed in
  cmake_parse_arguments(RP "" "${singleValues}" "" ${ARGN})

  string(REGEX MATCH "TARGET_OBJECTS:([^ >]+)" _source ${RP_FILE})

  # If expression was found, SOURCEFILE is a generator-expression for an object
  # library. Currently we found no way to call this function automatic for the
  # referenced target, so it must be called in the directory of the object
  # library definition.
  if(NOT "${_source}" STREQUAL "")
    set(${RP_RESULT_VARIABLE}
        ""
        PARENT_SCOPE)
    return()
  endif()

  string(REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" FILE "${RP_FILE}")

  if(IS_ABSOLUTE ${FILE})
    file(RELATIVE_PATH FILE ${CMAKE_CURRENT_SOURCE_DIR} ${RP_FILE})
  endif()

  # get the right path for file
  string(REPLACE ".." "__" PATH "${RP_FILE}")

  set(${RP_RESULT_VARIABLE}
      "${PATH}"
      PARENT_SCOPE)
endfunction()
