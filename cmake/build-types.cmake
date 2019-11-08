# Set a default build type for single-configuration CMake generators if no build
# type is set.

set(allowableBuildTypes Debug Release RelWithDebInfo MinSizeRel)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE
        STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    string(CONCAT IN_BUILD_ERROR
            "In-source builds not allowed. Please make a new directory "
            "(called a build directory) and run CMake from there. "
            "You may need to remove CMakeCache.txt.")

    message(FATAL_ERROR "${IN_BUILD_ERROR}")
endif()
