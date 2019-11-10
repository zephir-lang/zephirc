# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# CLI commands
add_subdirectory(commands)

find_package(yaml-cpp 0.6.0 REQUIRED)

# Add definition for compiler library.
add_library(compiler STATIC
    config.cpp)

target_include_directories(compiler
    PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(commands
    PUBLIC yaml-cpp)

if(CODE_COVERAGE)
    target_code_coverage(compiler AUTO ALL)
endif()

# Main
add_executable(zephir main.cpp)
target_link_libraries(zephir
    PRIVATE stdc++fs compiler commands)

if(CODE_COVERAGE)
    target_code_coverage(zephir AUTO ALL)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
