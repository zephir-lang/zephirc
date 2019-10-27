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
