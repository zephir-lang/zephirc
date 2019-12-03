# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for filesystem library.
add_library(filesystem SHARED filesystem.cpp)

# Instruments the library
target_code_coverage(filesystem AUTO ALL)
