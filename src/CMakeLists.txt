# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Zephir libraries
add_subdirectory(console)
add_subdirectory(filesystem)
add_subdirectory(config)
add_subdirectory(logger)

# Main
add_executable(${APP_TARGET} MACOSX_BUNDLE main.cpp)

target_include_directories(
  ${APP_TARGET}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(${APP_TARGET} PUBLIC console)

# Adds the executable to the 'ccov' and 'ccov-all' targets and excludes the file
# itself via regex
target_code_coverage(${APP_TARGET} AUTO ALL EXTERNAL)
