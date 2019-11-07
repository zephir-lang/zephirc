# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Include the sanitizer module
include(code-coverage)

# This introduces the 'ccov-all' targets
add_code_coverage_all_targets()

add_subdirectory(commands)

# The executable
add_executable(zephir main.cpp)
target_link_libraries(zephir PUBLIC commands)

# Adds the executable to the 'ccov' and 'ccov-all' targets
# and excludes the file itself via regex
target_code_coverage(zephir AUTO ALL)

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
