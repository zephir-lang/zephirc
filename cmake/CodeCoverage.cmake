# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

option(CODE_COVERAGE "Builds targets with code coverage instrumentation." OFF)

# Code Coverage Configuration
add_library(ccov INTERFACE)

if(CODE_COVERAGE)
  find_package(Lcov)
endif()

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|[Cc]lang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(ccov INTERFACE -O0 -g --coverage)
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(ccov INTERFACE --coverage)
  else()
    target_link_libraries(ccov INTERFACE --coverage)
  endif()
endif()
