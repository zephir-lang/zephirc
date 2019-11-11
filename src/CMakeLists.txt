# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# CLI commands
add_subdirectory(commands)

add_library(compiler STATIC filesystem.cpp config.cpp)

find_package(YamlCpp REQUIRED)
target_include_directories(compiler
                           PUBLIC ${YAMLCPP_INCLUDE_DIR}
                                  ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(commands PRIVATE ${YAMLCPP_LIBRARY})

if(CODE_COVERAGE)
  target_code_coverage(compiler AUTO ALL)
endif()

# Main
add_executable(zephir main.cpp)
target_link_libraries(zephir PRIVATE compiler commands)

if(CODE_COVERAGE)
  target_code_coverage(zephir AUTO ALL)
endif()

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
