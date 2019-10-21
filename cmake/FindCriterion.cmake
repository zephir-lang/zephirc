# Once done this will define
#
#  CRITERION_FOUND - System has Criterion
#  CRITERION_INCLUDE_DIRS - The Criterion include directories
#  CRITERION_LIBRARIES - The libraries needed to use Criterion

find_package(PkgConfig)

find_path(criterion_INCLUDE_DIR
        NAMES criterion/criterion.h
        PATHS /usr /usr/local /opt /opt/local
        PATH_SUFFIXES include
)

find_library(criterion_LIBRARY
        NAMES criterion libcriterion
        PATHS /usr /usr/local /opt /opt/local
        PATH_SUFFIXES lib
)

#set(CRITERION_LIBRARIES ${CRITERION_LIBRARY})
#set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})

set(criterion_INCLUDE_DIRS "${criterion_INCLUDE_DIR}")
set(criterion_LIBRARIES "${criterion_LIBRARY}")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
        criterion
        REQUIRED_VARS criterion_INCLUDE_DIR criterion_LIBRARY)

set(criterion_FOUND "${CRITERION_FOUND}")

if (criterion_FOUND)
    message(STATUS "> criterion found")
    if (NOT TARGET criterion::criterion)
        add_library(criterion::criterion UNKNOWN IMPORTED)
    endif ()

    set_target_properties(criterion::criterion PROPERTIES
            IMPORTED_LOCATION "${criterion_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${criterion_INCLUDE_DIRS}")

    message(STATUS ">\t${criterion_LIBRARIES}")
    message(STATUS ">\t${criterion_INCLUDE_DIRS}")
else ()
    message(STATUS "> criterion not found")
endif ()

# mark_as_advanced(CRITERION_INCLUDE_DIR CRITERION_LIBRARY)
mark_as_advanced(criterion_INCLUDE_DIRS)
mark_as_advanced(criterion_LIBRARIES)
