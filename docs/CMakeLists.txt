# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

find_package(Doxygen REQUIRED)

# set the input and output documentation paths
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${PROJECT_BINARY_DIR}/docs)

# configure the source Doxyfile by copying it and replacing all @variables@
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/docs/Doxyfile.in
               ${DOXYGEN_CONFIGURED_INPUT} @ONLY)
configure_file(${DOXYGEN_INPUT_DIR}/docs/header.html.in
               ${DOXYGEN_OUTPUT_DIR}/header.html @ONLY)

# copy the files needed by the documentation
configure_file(${DOXYGEN_INPUT_DIR}/docs/doxygen.css
               ${DOXYGEN_OUTPUT_DIR}/html/doxygen.css COPYONLY)
configure_file(${DOXYGEN_INPUT_DIR}/docs/jquery-3.2.1.min.js
               ${DOXYGEN_OUTPUT_DIR}/html/jquery-3.2.1.min.js COPYONLY)

# target setup
add_custom_target(
  doc ALL
  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
  COMMAND ${CMAKE_COMMAND} -E echo "Done."
  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

# setup install rules
install(
  FILES ${DOXYGEN_OUTPUT_DIR}/Zephir.tag
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
  COMPONENT doc)

install(
  DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
  DESTINATION ${CMAKE_INSTALL_DOCDIR}
  COMPONENT doc)
