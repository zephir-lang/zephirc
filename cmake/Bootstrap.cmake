# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Set a default build type for single-configuration CMake generators if no build
# type is set.

set(allowableBuildTypes Debug Release RelWithDebInfo MinSizeRel)
# Specify the build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE STRING
            "Specify the build type: Debug Release RelWithDebInfo MinSizeRel"
            FORCE)
elseif(NOT CMAKE_BUILD_TYPE IN_LIST allowableBuildTypes)
  message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
endif()

unset(allowableBuildTypes)

# Make sure developers do not run cmake in the main project directory, to keep
# build artifacts from becoming clutter
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory "
      "(called a build directory) and run CMake from there. "
      "You may need to remove CMakeCache.txt.")
endif()

include(ProcessorCount)

processorcount(N)
if(NOT N EQUAL 0)
  set(BUILD_JOBS ${N})
else()
  message(
    WARNING
      "There's a problem determining the processor count. Set fallback to: 2")
  set(BUILD_JOBS 2)
endif()
