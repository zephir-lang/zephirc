# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

set(CMAKE_COMPILER_IS_CLANG OFF)
set(CMAKE_COMPILER_IS_APPLE_CLANG OFF)

if("${CMAKE_C_COMPILER_ID}" MATCHES "[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}"
                                                  MATCHES "[Cc]lang")
  if("${CMAKE_C_COMPILER_ID}" MATCHES "Apple" OR "${CMAKE_CXX_COMPILER_ID}"
                                                 MATCHES "Apple")
    message(STATUS "Used compiler: Apple Clang")
    set(CMAKE_COMPILER_IS_APPLE_CLANG ON)
  else()
    message(STATUS "Used compiler: Clang")
    set(CMAKE_COMPILER_IS_CLANG ON)
  endif()
else()
  message(STATUS "Used compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# TODO(klay): Add MSVC check
# TODO(klay): Recheck with Apple Clang
if(CMAKE_COMPILER_IS_CLANG)
  if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 4)
    message(FATAL_ERROR "Clang version must be 4.0.0 or greater. Aborting...")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCXX)
  if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 7)
    message(FATAL_ERROR "Gcc version must be 7.0.0 or greater. Aborting...")
  endif()
endif()

# compiler-detect.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
