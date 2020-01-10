# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
# (c) 2018 George Cave <gcave@stablecoder.ca>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(CMakeDependentOption)

option(WARNINGS_AS_ERRORS "Turn all build warnings into errors")

# Special target that adds warnings. Is not exported.
add_library(zephir_warnings INTERFACE)

# Setup initial compiler flags to use on UNIX systems
set(unix-warnings -Wall -Wextra -pedantic -Wshadow -Wsign-conversion
                  -Wswitch-enum)

# This is recognized as a valid compiler flag only by gcc
if(CMAKE_COMPILER_IS_GNUCXX)
  list(APPEND unix-warnings -Weffc++)
endif()

target_compile_options(
  zephir_warnings
  INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/W4 $<$<BOOL:${WARNINGS_AS_ERRORS}>:/WX>>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${unix-warnings}
            $<$<BOOL:${WARNINGS_AS_ERRORS}>:-Werror>>)
