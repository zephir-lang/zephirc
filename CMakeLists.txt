cmake_minimum_required(VERSION 3.10)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE STRING
            "Directory to install zig to" FORCE)
endif()

project(zephir CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package(RE2C)

if (NOT RE2C_EXECUTABLE)
    message(FATAL_ERROR "\
\nNo re2c executable found in the $PATH. \
Consider install re2c or/and add re2c executable to the $PATH.")
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
