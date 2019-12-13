# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Add definition for config library.
file(GLOB CONFIG_YAML ${CMAKE_CURRENT_SOURCE_DIR}/config/yaml/*.cpp)
add_library(
  config SHARED ${CONFIG_YAML} config/stubs.cpp config/optimizations.cpp
                config/requires.cpp config/extra.cpp config.cpp)

target_include_directories(
  config PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Instruments the library
target_code_coverage(config AUTO ALL)

target_link_libraries(config PUBLIC CONAN_PKG::yaml-cpp filesystem)
