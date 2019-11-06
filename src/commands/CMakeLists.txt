# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

find_package(RE2C REQUIRED)
set(RE2C_OLDEST_VALIDATED_VERSION "0.16.0")

if("${RE2C_VERSION}" VERSION_LESS ${RE2C_OLDEST_VALIDATED_VERSION})
    message(FATAL_ERROR
            "re2c is too old, found ${RE2C_VERSION} and we need at last 0.16.0")
endif()

# Usage RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]
RE2C_TARGET(
    NAME options
    INPUT options.re
    OUTPUT options.cpp
    DEPENDS options.hpp
    COMPILE_FLAGS -W -Werror -c)

# Add definition for commands library.
add_library(commands STATIC
    parse_result.hpp
    optionexception.cpp
    optionexception.hpp
    "${RE2C_options_OUTPUTS}")

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
