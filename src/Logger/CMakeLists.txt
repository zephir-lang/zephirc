# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for Logger facade library.
add_library(logger SHARED Logger.cpp)

target_include_directories(
  logger PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(logger PRIVATE zephir_warnings CONAN_PKG::yaml-cpp
                                     CONAN_PKG::spdlog)

code_coverage(logger)
