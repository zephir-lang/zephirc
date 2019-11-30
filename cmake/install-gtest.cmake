# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_SHALLOW 1
  GIT_TAG release-1.10.0)

FetchContent_GetProperties(googletest)

# Disable cppcheck for googletest
set(CMAKE_CXX_CPPCHECK_ORIGIN "${CMAKE_CXX_CPPCHECK}")
set(CMAKE_CXX_CPPCHECK
    ""
    CACHE STRING "" FORCE)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

# Restore cppcheck configuration
set(CMAKE_CXX_CPPCHECK_ORIGIN "${CMAKE_CXX_CPPCHECK}")
set(CMAKE_CXX_CPPCHECK "${CMAKE_CXX_CPPCHECK_ORIGIN}")

# install-gtest.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
