# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# CLI commands
add_subdirectory(commands)

find_package(PkgConfig REQUIRED)

# Resolve system dependency on yaml-cpp, which apparently does not
# provide a CMake find_package() module.
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)

find_path(YAML_CPP_INCLUDE_DIR
    NAMES yaml_cpp.h
    PATHS ${YAML_CPP_INCLUDE_DIRS})

find_library(YAML_CPP_LIBRARY
    NAMES YAML_CPP
    PATHS ${YAML_CPP_LIBRARY_DIRS})

link_directories(${YAML_CPP_LIBRARY_DIRS})

# Add definition for compiler library.
add_library(compiler STATIC
    config.cpp)

target_include_directories(compiler
    PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(commands
    PUBLIC ${YAML_CPP_LIBRARIES})

if(CODE_COVERAGE)
    target_code_coverage(compiler AUTO ALL)
endif()

# Main
add_executable(zephir main.cpp)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(zephir
        PRIVATE stdc++fs compiler commands)
else()
    target_link_libraries(zephir
        PRIVATE compiler commands)
endif()

if(CODE_COVERAGE)
    target_code_coverage(zephir AUTO ALL)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
