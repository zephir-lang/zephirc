# FindCriterion.cmake
#
# This module finds an installed Criterion package.
# The module defines the following variables:
#
#  CRITERION_FOUND       - System has Criterion
#  CRITERION_INCLUDE_DIR - The Criterion include directories
#  CRITERION_LIBRARIES   - The libraries needed to use Criterion

if (UNIX)
    find_path(CRITERION_INCLUDE_DIR
            NAMES criterion/criterion.h
            PATHS $ENV{CRITERION_INCLUDE_DIR} /usr /usr/local
            PATH_SUFFIXES include
            DOC "Criterion header location.")

    find_library(CRITERION_LIBRARIES
            NAMES criterion libcriterion
            PATHS $ENV{CRITERION_LIBRARIES} /usr /usr/local
            PATH_SUFFIXES lib
            DOC "Criterion library location.")
elseif (WIN32)
    find_path(CRITERION_INCLUDE_DIR
            NAMES criterion/criterion.h
            PATHS $ENV{CRITERION_INCLUDE_DIR} C:/
            PATH_SUFFIXES include
            DOC "Criterion header location.")

    find_library(CRITERION_LIBRARIES
            NAMES criterion libcriterion
            PATHS $ENV{CRITERION_LIBRARIES} C:/
            PATH_SUFFIXES "" Debug Release lib
            DOC "Criterion library location.")
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
        Criterion
        REQUIRED_VARS CRITERION_INCLUDE_DIR CRITERION_LIBRARIES)

if (CRITERION_FOUND)
    if (NOT Criterion_FIND_QUIETLY)
        message(STATUS "> criterion found")
    endif()

    if (NOT TARGET criterion::criterion)
        add_library(criterion::criterion UNKNOWN IMPORTED)
    endif ()

    set_target_properties(criterion::criterion PROPERTIES
            IMPORTED_LOCATION "${CRITERION_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${CRITERION_INCLUDE_DIR}")

    if (NOT Criterion_FIND_QUIETLY)
        message(STATUS ">\t${CRITERION_LIBRARIES}")
        message(STATUS ">\t${CRITERION_INCLUDE_DIR}")
    endif()
else ()
    if (Criterion_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Criterion")
    elseif(NOT Criterion_FIND_QUIETLY)
        message(STATUS "> criterion not found")
    endif()
endif ()

mark_as_advanced(CRITERION_INCLUDE_DIR)
mark_as_advanced(CRITERION_LIBRARIES)
