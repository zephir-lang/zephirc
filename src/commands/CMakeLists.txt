# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for commands library.
add_library(commands STATIC
    commands.cpp
    formatter.cpp)

target_include_directories(commands PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(commands PUBLIC CLI11)

if(CODE_COVERAGE)
    target_code_coverage(commands AUTO ALL)
endif()
