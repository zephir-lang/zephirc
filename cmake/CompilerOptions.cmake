# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
# (c) 2018 George Cave <gcave@stablecoder.ca>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(CMakeDependentOption)

option(WARNINGS_AS_ERRORS "Turn all build warnings into errors")

list(APPEND force-libcxx "CMAKE_CXX_COMPILER_ID STREQUAL \"Clang\"")
list(APPEND force-libcxx "CMAKE_SYSTEM_NAME STREQUAL \"Linux\"")
list(APPEND force-libcxx "CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME")

# This macro provides ZEPHIR_FORCE_LIBCXX option to the user only if a set of
# `force-libcxx' conditions are true.
cmake_dependent_option(
  ZEPHIR_FORCE_LIBCXX
  "Force clang to use libc++ instead of libstdc++ (Linux only)" OFF
  "${force-libcxx}" OFF)

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
  INTERFACE $<$<BOOL:${ZEPHIR_FORCE_LIBCXX}>:-stdlib=libc++>
            $<$<CXX_COMPILER_ID:MSVC>:/W4
            $<$<BOOL:${WARNINGS_AS_ERRORS}>:/WX>>
            $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:${unix-warnings}
            $<$<BOOL:${WARNINGS_AS_ERRORS}>:-Werror>>)

if(NOT CMAKE_VERSION VERSION_LESS 3.13)
  target_link_options(zephir_warnings INTERFACE
                      $<$<BOOL:${ZEPHIR_FORCE_LIBCXX}>:-stdlib=libc++>)
endif()
