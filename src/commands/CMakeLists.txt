# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

find_package(Re2c REQUIRED)
set(RE2C_OLDEST_VALIDATED_VERSION "0.16.0")

if ("${RE2C_VERSION}" VERSION_LESS ${RE2C_OLDEST_VALIDATED_VERSION})
    message(FATAL_ERROR
            "re2c is too old, found ${RE2C_VERSION} and we need at last 0.16.0")
endif ()

# Usage RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]
re2c_target(commands
        "${CMAKE_SOURCE_DIR}/src/commands/options.re"
        "${CMAKE_SOURCE_DIR}/src/commands/options.cpp"
        COMPILE_FLAGS
        "-W -Werror -c")

# Add definition for commands library.
add_library(commands STATIC
            cmd.hpp
            optionexception.cpp
            optionexception.hpp
            "${RE2C_commands_OUTPUTS}")

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
