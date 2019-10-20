cmake_minimum_required(VERSION 3.10)

project(zephir LANGUAGES CXX VERSION 1.0.0)

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Set a default build type for single-configuration
# CMake generators if no build type is set.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE STRING
            "Directory to install zephir to" FORCE)
endif ()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

include(CxxFlags)
include(CTest)
include(FindCppUnit)

add_subdirectory(src)

option(ZEPHIR_BUILD_TESTING "Build test project" OFF)

if (BUILD_TESTING AND ZEPHIR_BUILD_TESTING)
    message(STATUS "Include test sources")
    add_subdirectory(test)
endif()
