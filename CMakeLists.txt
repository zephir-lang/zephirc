cmake_minimum_required(VERSION 3.11)
include("${CMAKE_SOURCE_DIR}/cmake/version.cmake")

project(zephir LANGUAGES CXX VERSION "${VERSION}")

# Provide path for cmake scripts
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(BuildTypes)

set(CMAKE_CXX_STANDARD 11)
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

option(ZEPHIR_BUILD_TESTING "Build test project" OFF)
option(ZEPHIR_CODE_COVERAGE "Enable code coverage metrics" OFF)

add_subdirectory(src)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING AND ZEPHIR_BUILD_TESTING)
    include(cppcheck)

    message(STATUS "Include test sources")
    add_subdirectory(test)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
