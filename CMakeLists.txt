cmake_minimum_required(VERSION 3.10)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp" zephir_version
        REGEX "#define ZEPHIR_VERSION_(MAJOR|MINOR|PATCH)")

foreach(part ${zephir_version})
    if(part MATCHES "#define ZEPHIR_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(ZEPHIR_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()

set(VERSION ${ZEPHIR_VERSION_MAJOR}.${ZEPHIR_VERSION_MINOR}.${ZEPHIR_VERSION_PATCH})

project(zephir LANGUAGES CXX VERSION "${VERSION}")

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Set a default build type for single-configuration CMake generators if no build
# type is set.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE
        STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif ()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_BINARY_DIR}"
      CACHE STRING "Directory to install zephir to" FORCE)
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

add_subdirectory(src)

option(ZEPHIR_BUILD_TESTING "Build test project" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING AND ZEPHIR_BUILD_TESTING)
    message(STATUS "Include test sources")
    add_subdirectory(test)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
