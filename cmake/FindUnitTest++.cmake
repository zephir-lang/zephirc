# FindUnitTest++.cmake
#
# This module finds an installed UnitTest++ package.
# The module defines the following variables:

if (UNIX)
    find_path(UNITTEST++_INCLUDE_DIR
            NAMES UnitTest++/UnitTest++.h
            PATHS $ENV{UNITTEST++_INCLUDE_DIR} /usr /usr/local
            PATH_SUFFIXES include
            DOC "UnitTest++ header location.")

    find_library(UNITTEST++_LIBRARIES
            NAMES UnitTest++
            PATHS $ENV{UNITTEST++_LIBRARIES} /usr /usr/local
            PATH_SUFFIXES lib
            DOC "UnitTest++ library location.")
elseif (WIN32)
    find_path(UNITTEST++_INCLUDE_DIR
            NAMES UnitTest++/UnitTest++.h
            PATHS $ENV{UNITTEST++_INCLUDE_DIR} C:/
            PATH_SUFFIXES include
            DOC "UnitTest++ header location.")

    find_library(UNITTEST++_LIBRARIES
            NAMES UnitTest++ UnitTest++.vsnet2005 UnitTest++.vsnet2008
            PATHS $ENV{UNITTEST++_LIBRARIES} C:/
            PATH_SUFFIXES "" Debug Release lib
            DOC "UnitTest++ library location.")
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
        UnitTest++
        REQUIRED_VARS UNITTEST++_INCLUDE_DIR UNITTEST++_LIBRARIES)

if (UNITTEST++_FOUND)
    if (NOT UnitTest++_FIND_QUIETLY)
        message(STATUS "> UnitTest++ found")
    endif()

    if (NOT TARGET UnitTest++)
        add_library(UnitTest++ UNKNOWN IMPORTED)
    endif ()

    set_target_properties(UnitTest++ PROPERTIES
            IMPORTED_LOCATION "${UNITTEST++_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${UNITTEST++_INCLUDE_DIR}")

    if (NOT UnitTest++_FIND_QUIETLY)
        message(STATUS ">\t${UNITTEST++_LIBRARIES}")
        message(STATUS ">\t${UNITTEST++_INCLUDE_DIR}")
    endif()
else ()
    if (UnitTest++_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find UnitTest++")
    elseif(NOT UnitTest++_FIND_QUIETLY)
        message(STATUS "> UnitTest++ not found. Try to set UNITTEST++_INCLUDE_DIR and UNITTEST++_LIBRARIES")
    endif()
endif ()

mark_as_advanced(UNITTEST++_INCLUDE_DIR)
mark_as_advanced(UNITTEST++_LIBRARIES)
