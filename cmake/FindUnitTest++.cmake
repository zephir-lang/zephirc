# FindUnitTest++.cmake
#
# This module finds an installed UnitTest++ package.
# The module defines the following variables:
#
#  UNITTESTXX_FOUND       - System has UnitTest++
#  UNITTESTXX_INCLUDE_DIR - The UnitTest++ include directories
#  UNITTESTXX_LIBRARIES   - The libraries needed to use UnitTest++

if (UNIX)
    find_path(UNITTESTXX_INCLUDE_DIR
            NAMES UnitTest++/UnitTest++.h
            PATHS $ENV{UNITTESTXX_INCLUDE_DIR} /usr /usr/local
            PATH_SUFFIXES include
            DOC "UnitTest++ header location.")

    find_library(UNITTESTXX_LIBRARIES
            NAMES UnitTest++
            PATHS $ENV{UNITTESTXX_LIBRARIES} /usr /usr/local
            PATH_SUFFIXES lib
            DOC "UnitTest++ library location.")
elseif (WIN32)
    find_path(UNITTESTXX_INCLUDE_DIR
            NAMES UnitTest++/UnitTest++.h
            PATHS $ENV{UNITTESTXX_INCLUDE_DIR} C:/
            PATH_SUFFIXES include
            DOC "UnitTest++ header location.")

    find_library(UNITTESTXX_LIBRARIES
            NAMES UnitTest++ UnitTest++.vsnet2005 UnitTest++.vsnet2008
            PATHS $ENV{UNITTESTXX_LIBRARIES} C:/
            PATH_SUFFIXES "" Debug Release lib
            DOC "UnitTest++ library location.")
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
        UnitTest++
        REQUIRED_VARS UNITTESTXX_INCLUDE_DIR UNITTESTXX_LIBRARIES)

set (UNITTESTXX_FOUND ${UNITTEST++_FOUND})

if (UNITTEST++_FOUND)
    if (NOT UnitTest++_FIND_QUIETLY)
        message(STATUS "> UnitTest++ found")
    endif()

    if (NOT TARGET UnitTest++)
        add_library(UnitTest++ UNKNOWN IMPORTED)
    endif ()

    set_target_properties(UnitTest++ PROPERTIES
            IMPORTED_LOCATION "${UNITTESTXX_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${UNITTESTXX_INCLUDE_DIR}")

    if (NOT UnitTest++_FIND_QUIETLY)
        message(STATUS ">\t${UNITTESTXX_LIBRARIES}")
        message(STATUS ">\t${UNITTESTXX_INCLUDE_DIR}")
    endif()
else ()
    if (UnitTest++_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find UnitTest++")
    elseif(NOT UnitTest++_FIND_QUIETLY)
        message(STATUS "> UnitTest++ not found. Try to set UNITTESTXX_INCLUDE_DIR and UNITTESTXX_LIBRARIES")
    endif()
endif ()

mark_as_advanced(UNITTESTXX_INCLUDE_DIR)
mark_as_advanced(UNITTESTXX_LIBRARIES)
