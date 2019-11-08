# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# CLI commands
add_subdirectory(commands)



# Main
add_executable(zephir main.cpp)
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
