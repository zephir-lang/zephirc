cmake_minimum_required(VERSION 3.10)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE STRING
            "Directory to install zephir to" FORCE)
endif ()

project(zephir LANGUAGES CXX VERSION 1.0.0)

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package(RE2C REQUIRED)
set(RE2C_OLDEST_VALIDATED_VERSION "0.16.0")

if ("${RE2C_VERSION}" VERSION_LESS ${RE2C_OLDEST_VALIDATED_VERSION})
    message(FATAL_ERROR "re2c is too old, found ${RE2C_VERSION} and we need at last 0.16.0")
endif()

# Usage RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]
RE2C_TARGET(command
        src/command/scanner.re
        "${CMAKE_SOURCE_DIR}/src/command/scanner.cpp"
        COMPILE_FLAGS "-W")

# Add definition for optparser library.
add_library(command src/command/scanner.hpp "${RE2C_command_OUTPUTS}")

add_executable(zephir src/main.cpp)
target_link_libraries(zephir command)
