# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Zephir libraries
add_subdirectory(Console)
add_subdirectory(FileSystem)
add_subdirectory(Config)

# TODO(alexndr.mac): Rename directory and files to follow PascalCase style
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
  PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${ZEPHIR_PACKAGE_NAME}
             MACOSX_BUNDLE_BUNDLE_VERSION "${ZEPHIR_PACKAGE_VERSION}"
             MACOSX_BUNDLE_SHORT_VERSION_STRING ${ZEPHIR_VERSION}
             MACOSX_BUNDLE_LONG_VERSION_STRING ${ZEPHIR_VERSION_FULL}
             MACOSX_BUNDLE_COPYRIGHT "${ZEPHIR_COPYRIGHT}"
             MACOSX_BUNDLE_INFO_STRING "${ZEPHIR_COPYRIGHT}"
             MACOSX_BUNDLE_GUI_IDENTIFIER com.zephir-lang.zephir)

target_link_libraries(${ZEPHIR_APP_TARGET} PUBLIC console)

# Adds the executable to the 'gcov' and 'lcov' targets
code_coverage(${ZEPHIR_APP_TARGET})
