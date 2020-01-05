# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

find_package(Doxygen)

option(ZEPHIR_BUILD_DOC
       "ON to generate the API documentation, OFF to ignore it"
       ${DOXYGEN_FOUND})

if(ZEPHIR_BUILD_DOC)
  if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
  endif()

  # set the input and output documentation paths
  set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
  set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)

  # configure the source Doxyfile by copying it and replacing all @variables@
  set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
  configure_file(${DOXYGEN_INPUT_DIR}/docs/Doxyfile.in
                 ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

  # copy the files needed by the documentation
  configure_file(${DOXYGEN_INPUT_DIR}/docs/doxygen.css
                 ${DOXYGEN_OUTPUT_DIR}/html/doxygen.css COPYONLY)

  # target setup
  add_custom_target(
    doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
    WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR}
    COMMENT "Building API Documentation...")

  set(_path "file://${DOXYGEN_OUTPUT_DIR}/html/index.html")
  add_custom_command(
    TARGET doc
    POST_BUILD
    COMMAND ;
    COMMENT "Open ${_path} in your browser to view the API Documentation.")
  unset(_path)

  # setup install rules
  install(
    FILES ${DOXYGEN_OUTPUT_DIR}/Zephir.tag
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT doc)

  install(
    DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
    COMPONENT doc)
endif()
