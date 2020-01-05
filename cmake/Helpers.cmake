# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Get the language of a source file.
#
# ~~~
# Required:
# FILE - The source file.
# RESULT_VARIABLE - The result variable.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>
# ~~~
function(detect_language FILE RESULT_VARIABLE)
  get_filename_component(FILE_EXT "${FILE}" EXT)

  string(TOLOWER "${FILE_EXT}" FILE_EXT)
  string(SUBSTRING "${FILE_EXT}" 1 -1 FILE_EXT)

  get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
  foreach(LANG ${ENABLED_LANGUAGES})
    list(FIND CMAKE_${LANG}_SOURCE_FILE_EXTENSIONS "${FILE_EXT}" TEMP)
    if(NOT ${TEMP} EQUAL -1)
      set(${RESULT_VARIABLE}
          "${LANG}"
          PARENT_SCOPE)
      return()
    endif()
  endforeach()

  set(${RESULT_VARIABLE}
      ""
      PARENT_SCOPE)
endfunction()

# Get the relative path of the source file destination path.
#
# ~~~
# This path is needed by FindGcov and FindLcov CMake files to locate the
# captured data.
#
# Required:
# SOURCEFILE - The source file destination path.
# RESULT_VARIABLE - The result variable.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>
# ~~~
function(relative_path SOURCEFILE RESULT_VARIABLE)
  string(REGEX MATCH "TARGET_OBJECTS:([^ >]+)" _source ${SOURCEFILE})

  # If expression was found, SOURCEFILE is a generator-expression for an object
  # library. Currently we found no way to call this function automatic for the
  # referenced target, so it must be called in the directory of the object
  # library definition.
  if(NOT "${_source}" STREQUAL "")
    set(${RESULT_VARIABLE}
        ""
        PARENT_SCOPE)
    return()
  endif()

  string(REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" FILE "${SOURCEFILE}")

  if(IS_ABSOLUTE ${FILE})
    file(RELATIVE_PATH FILE ${CMAKE_CURRENT_SOURCE_DIR} ${FILE})
  endif()

  # get the right path for file
  string(REPLACE ".." "__" PATH "${FILE}")

  set(${RESULT_VARIABLE}
      "${PATH}"
      PARENT_SCOPE)
endfunction()
