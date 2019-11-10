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
pkg_check_modules(YAML_CPP yaml-cpp)

find_path(YAML_CPP_INCLUDE_DIR
    NAMES yaml.h
    PATHS ${YAML_CPP_INCLUDE_DIRS})

find_library(YAML_CPP_LIBRARY
    NAMES yaml-cpp
    PATHS ${YAML_CPP_LIBRARY_DIRS})

# TODO(klay): Do we need this line?
link_directories(${YAML_CPP_LIBRARY_DIRS})

add_library(compiler STATIC
    filesystem.cpp
    config.cpp)

target_include_directories(compiler
    PUBLIC ${YAML_CPP_INCLUDE_DIRS}
           ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(commands
    PRIVATE ${YAML_CPP_LIBRARY})

if(CODE_COVERAGE)
    target_code_coverage(compiler AUTO ALL)
endif()

# Main
add_executable(zephir main.cpp)
target_link_libraries(zephir
    PRIVATE compiler commands)

if(CODE_COVERAGE)
    target_code_coverage(zephir AUTO ALL)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
