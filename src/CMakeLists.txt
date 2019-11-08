# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

if(CODE_COVERAGE)
    add_code_coverage()
endif()

# The executable
add_executable(zephir main.cpp)

add_subdirectory(commands)
target_link_libraries(zephir PRIVATE commands)

if(CODE_COVERAGE)
    target_code_coverage(zephir)
endif()

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
