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
add_executable(${ZEPHIR_APP_TARGET} MACOSX_BUNDLE main.cpp)

target_include_directories(
  ${ZEPHIR_APP_TARGET}
  PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

set_target_properties(
  ${ZEPHIR_APP_TARGET}
  PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_DISPLAY_NAME}
             MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}${BUILD_SUFFIX}"
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
             MACOSX_BUNDLE_COPYRIGHT "${ZEPHIR_COPYRIGHT}"
             MACOSX_BUNDLE_INFO_STRING "${ZEPHIR_COPYRIGHT}"
             MACOSX_BUNDLE_GUI_IDENTIFIER com.zephir-lang.zephir)

target_link_libraries(${ZEPHIR_APP_TARGET} PUBLIC console)

# Adds the executable to the 'gcov' and 'lcov' targets
code_coverage(${ZEPHIR_APP_TARGET})
