# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(GNUInstallDirs)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
      "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
      "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
      "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()

set(ZEPHIR_DATA_DIR "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")
set(ZEPHIR_OUTPUT_DIR "${zephir_BINARY_DIR}/${ZEPHIR_DATA_DIR}")
set(ZEPHIR_EXE_DIR "${zephir_BINARY_DIR}/bin")
