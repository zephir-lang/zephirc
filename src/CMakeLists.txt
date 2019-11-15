# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

include(cppcheck)

# Zephir libraries
add_subdirectory(commands)
add_subdirectory(filesystem)
add_subdirectory(config)

# Main
add_executable(zephir main.cpp)
target_link_libraries(zephir PRIVATE config)

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
