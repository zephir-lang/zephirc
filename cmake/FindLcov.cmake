# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>

# configuration
set(LCOV_DATA_PATH "${CMAKE_BINARY_DIR}/ccov/data")
set(LCOV_DATA_PATH_INIT
    "${LCOV_DATA_PATH}/init"
    CACHE PATH "Where to put initial coverage")
set(LCOV_DATA_PATH_CAPTURE
    "${LCOV_DATA_PATH}/capture"
    CACHE PATH "Where to put final coverage")
set(LCOV_HTML_PATH
    "${CMAKE_BINARY_DIR}/ccov/html"
    CACHE PATH "Where to put html coverage reports")

# Search for Gcov which is used by Lcov.
find_package(Gcov)

# Add lcov evaluation for target <TARGET_NAME>.
#
# ~~~
# Only sources of this target will be evaluated and no dependencies will be
# added. It will call geninfo on any source file of <TARGET_NAME> once and store
# the info file in the same directory.
#
# Note: This function is only a wrapper to define this function always, even if
#   coverage is not supported by the compiler or disabled. This function must
#   be defined here, because the module will be exited, if there is no coverage
#   support by the compiler or it is disabled by the user.
#
# Required:
# TARGET_NAME - The target name add lcov evaluation to.
# ~~~
function(add_lcov_target TARGET_NAME)
  if(LCOV_FOUND)
    # capture initial coverage data
    lcov_target_initial(${TARGET_NAME})

    # capture coverage data after execution
    lcov_capture_target(${TARGET_NAME})
  endif()
endfunction()

# Include required Modules
include(FindPackageHandleStandardArgs)

# Search for required lcov binaries.
find_program(LCOV_EXE lcov lcov.bat lcov.exe lcov.perl)
find_program(GENINFO_EXE geninfo geninfo.exe)
find_program(GENHTML_EXE genhtml genhtml.perl genhtml.bat)

mark_as_advanced(LCOV_EXE GENINFO_EXE GENHTML_EXE)

find_package_handle_standard_args(
  lcov #
  REQUIRED_VARS LCOV_EXE GENINFO_EXE GENHTML_EXE)

# Enable demangle C++ function names, if c++filt is found.
set(GENHTML_CPPFILT_FLAG "")
find_program(CPPFILT_EXE c++filt)
mark_as_advanced(CPPFILT_EXE)

if(NOT CPPFILT_EXE STREQUAL "")
  set(GENHTML_CPPFILT_FLAG "--demangle-cpp")

  if(NOT CMAKE_REQUIRED_QUIET)
    message(STATUS "Found c++filt: ${CPPFILT_EXE}")
  endif()
endif()

# Enable no-external flag for lcov, if available.
if(GENINFO_EXE AND NOT DEFINED GENINFO_EXTERN_FLAG)
  set(FLAG "")
  execute_process(COMMAND ${GENINFO_EXE} --help OUTPUT_VARIABLE GENINFO_HELP)
  string(REGEX MATCH "external" GENINFO_RES "${GENINFO_HELP}")

  if(GENINFO_RES)
    set(FLAG "--no-external")
  endif()

  set(GENINFO_EXTERN_FLAG
      "${FLAG}"
      CACHE STRING "Geninfo flag to exclude system sources.")
endif()

# If Lcov was not found, exit module now.
if(NOT LCOV_FOUND)
  return()
endif()

# Create directories to be used.
file(MAKE_DIRECTORY ${LCOV_DATA_PATH_INIT})
file(MAKE_DIRECTORY ${LCOV_DATA_PATH_CAPTURE})

set(LCOV_REMOVE_PATTERNS "")
if(DEFINED COVERAGE_EXCLUDES)
  string(REPLACE ";" " " LCOV_REMOVE_PATTERNS "${COVERAGE_EXCLUDES}")
endif()

# Merges lcov files to a single target file.
#
# ~~~
# OUTFILE - The result file
# FILES - Tracefiles to combine the coverage data
# FLAGS - Additional lcov flags
# REMOVE_PATTERNS - Patterns to remove coverage data from a tracefile
# ~~~
function(lcov_merge_files)
  # Define the supported set of keywords
  set(prefix LMF)
  set(noValues "")
  set(singleValues OUTFILE)
  set(multiValues FILES FLAGS REMOVE_PATTERNS)

  # Process the arguments passed in
  cmake_parse_arguments(${prefix} "${noValues}" "${singleValues}"
                        "${multiValues}" ${ARGN})

  # Generate merged file.
  string(REPLACE "${CMAKE_BINARY_DIR}/" "" FILE_REL "${${prefix}_OUTFILE}")
  add_custom_command(
    OUTPUT "${${prefix}_OUTFILE}.raw"
    COMMAND cat ${${prefix}_FILES} > ${${prefix}_OUTFILE}.raw
    DEPENDS ${${prefix}_FILES}
    COMMENT "Generating file ${FILE_REL}")

  add_custom_command(
    OUTPUT ${${prefix}_OUTFILE}
    COMMAND
      ${LCOV_EXE} -q -a ${${prefix}_OUTFILE}.raw -o ${${prefix}_OUTFILE} --rc
      lcov_branch_coverage=1 -b ${PROJECT_SOURCE_DIR} ${${prefix}_FLAGS}
    COMMAND
      ${LCOV_EXE} -q -r ${${prefix}_OUTFILE} ${${prefix}_REMOVE_PATTERNS} --rc
      lcov_branch_coverage=1 -o ${${prefix}_OUTFILE} ${${prefix}_FLAGS}
    DEPENDS ${${prefix}_OUTFILE}.raw
    COMMENT "Post-processing file ${FILE_REL}")
endfunction()

# Add a new global target to generate initial coverage reports for all targets.
# This target will be used to generate the global initial info file, which is
# used to gather even empty report data.
if(NOT TARGET lcov-capture-init)
  add_custom_target(lcov-capture-init)
  define_property(
    GLOBAL
    PROPERTY LCOV_CAPTURE_INIT_FILES
    BRIEF_DOCS "List of all init capture files"
    FULL_DOCS "Empty capture files for the baseline coverage")
endif()

# Add initial capture of coverage data for target <TARGET_NAME>, which is needed
# to get also data for objects, which were not loaded at execution time. It will
# call geninfo for every source file of <TARGET_NAME> once and store the info
# file in the same directory.
#
# ~~~
# Required:
# TARGET_NAME - The target name to add initial capture of coverage data for.
# ~~~
function(lcov_target_initial TARGET_NAME)
  # We don't have to check, if the target has support for coverage, thus this
  # will be checked by target_code_coverage in CodeCoverage.cmake. Instead we
  # have to determine which gcov binary to use.
  get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)

  set(SOURCES "")
  set(TARGET_COMPILER "")

  foreach(FILE ${TARGET_SOURCES})
    relative_path(${FILE} FILE)
    if(NOT "${FILE}" STREQUAL "")
      detect_language(${FILE} LANG)
      if(NOT "${LANG}" STREQUAL "")
        list(APPEND SOURCES "${FILE}")
        set(TARGET_COMPILER ${CMAKE_${LANG}_COMPILER_ID})
      endif()
    endif()
  endforeach()

  # If no gcov binary was found, coverage data can't be evaluated.
  if(NOT GCOV_${TARGET_COMPILER}_EXE)
    message(
      WARNING "No coverage evaluation binary found for ${TARGET_COMPILER}.")
    return()
  endif()

  set(GCOV_EXE "${GCOV_${TARGET_COMPILER}_EXE}")

  get_target_property(TARGET_BIN_DIR ${TARGET_NAME} BINARY_DIR)
  set(TARGET_DIR ${TARGET_BIN_DIR}/CMakeFiles/${TARGET_NAME}.dir)

  set(GENINFO_FILES "")

  foreach(FILE ${SOURCES})
    # generate empty coverage files
    set(OUTFILE "${TARGET_DIR}/${FILE}.info.init")
    list(APPEND GENINFO_FILES ${OUTFILE})

    add_custom_command(
      OUTPUT ${OUTFILE}
      COMMAND
        ${GENINFO_EXE} -q -b ${PROJECT_SOURCE_DIR} -i --gcov-tool ${GCOV_EXE} -o
        ${OUTFILE} ${GENINFO_EXTERN_FLAG} ${TARGET_DIR}/${FILE}.gcno
      DEPENDS ${TARGET_NAME}
      COMMENT "Capturing initial coverage data for file ${FILE}")
  endforeach()

  # Concatenate all files generated by geninfo to a single file per target.
  set(OUTFILE "${LCOV_DATA_PATH_INIT}/${TARGET_NAME}.info")
  lcov_merge_files(
    OUTFILE "${OUTFILE}"
    FILES ${GENINFO_FILES}
    FLAGS "--initial"
    REMOVE_PATTERNS ${LCOV_REMOVE_PATTERNS})

  add_custom_target(
    ${TARGET_NAME}-capture-init ALL
    DEPENDS ${OUTFILE}
    COMMENT "Capturing initial coverage data for target ${TARGET_NAME}")

  # Add geninfo file generation to global lcov-geninfo target
  add_dependencies(lcov-capture-init ${TARGET_NAME}-capture-init)
  set_property(GLOBAL APPEND PROPERTY LCOV_CAPTURE_INIT_FILES "${OUTFILE}")
endfunction()

# Generate the global info file for all targets.
#
# ~~~
# It has to be called after all other CMake functions in the root CMakeLists.txt
# file, to get a full list of all targets that generate coverage data.
# ~~~
function(lcov_capture_initial)
  # Skip this function (and do not create the following targets), if there are
  # no input files.
  get_property(LCOV_CAPTURE_INIT_FILES GLOBAL PROPERTY LCOV_CAPTURE_INIT_FILES)
  if("${LCOV_CAPTURE_INIT_FILES}" STREQUAL "")
    return()
  endif()

  # Add a new target to merge the files of all targets.
  set(OUTFILE "${LCOV_DATA_PATH_INIT}/all-targets.info")
  lcov_merge_files(OUTFILE "${OUTFILE}" FILES ${LCOV_CAPTURE_INIT_FILES})

  add_custom_target(
    lcov-geninfo-init ALL
    DEPENDS ${OUTFILE} lcov-capture-init
    COMMENT "Capturing global initial coverage data")
endfunction()

# Add a new global target to generate coverage reports for all targets. This
# target will be used to generate the global info file.
if(NOT TARGET lcov-capture)
  add_custom_target(lcov-capture)
  define_property(
    GLOBAL
    PROPERTY LCOV_CAPTURE_FILES
    BRIEF_DOCS "List of all capture files"
    FULL_DOCS "All capture files which have coverage data included")
endif()

# Add capture of coverage data for target <TARGET_NAME>, which is needed to get
# also data for objects, which were not loaded at execution time. It will call
# geninfo for every source file of <TARGET_NAME> once and store the info file in
# the same directory.
#
# ~~~
# Required:
# TARGET_NAME - The target name to add capture of coverage data for.
# ~~~
function(lcov_capture_target TARGET_NAME)
  # We don't have to check, if the target has support for coverage, thus this
  # will be checked by target_code_coverage in CodeCoverage.cmake. Instead we
  # have to determine which gcov binary to use.
  get_target_property(TARGET_SOURCES ${TARGET_NAME} SOURCES)

  set(SOURCES "")
  set(TARGET_COMPILER "")

  foreach(FILE ${TARGET_SOURCES})
    relative_path(${FILE} FILE)
    if(NOT "${FILE}" STREQUAL "")
      detect_language(${FILE} LANG)
      if(NOT "${LANG}" STREQUAL "")
        list(APPEND SOURCES "${FILE}")
        set(TARGET_COMPILER ${CMAKE_${LANG}_COMPILER_ID})
      endif()
    endif()
  endforeach()

  # If no gcov binary was found, coverage data can't be evaluated.
  if(NOT GCOV_${TARGET_COMPILER}_EXE)
    message(
      WARNING "No coverage evaluation binary found for ${TARGET_COMPILER}.")
    return()
  endif()

  set(GCOV_EXE "${GCOV_${TARGET_COMPILER}_EXE}")

  get_target_property(TARGET_BIN_DIR ${TARGET_NAME} BINARY_DIR)
  set(TARGET_DIR ${TARGET_BIN_DIR}/CMakeFiles/${TARGET_NAME}.dir)

  set(GENINFO_FILES "")

  foreach(FILE ${SOURCES})
    # Generate coverage files. If no .gcda file was generated during execution,
    # the empty coverage file will be used instead.
    set(OUTFILE "${TARGET_DIR}/${FILE}.info")
    set(INFILE "${TARGET_DIR}/${FILE}.gcda")

    list(APPEND GENINFO_FILES ${OUTFILE})

    add_custom_command(
      OUTPUT ${OUTFILE}
      COMMAND
        test -f "${INFILE}" && ${GENINFO_EXE} -q -b ${PROJECT_SOURCE_DIR}
        --gcov-tool ${GCOV_EXE} -o ${OUTFILE} ${GENINFO_EXTERN_FLAG} ${INFILE}
        || cp ${OUTFILE}.init ${OUTFILE}
      DEPENDS ${TARGET_NAME} ${TARGET_NAME}-capture-init
      COMMENT "Capturing coverage data for file ${FILE}")
  endforeach()

  # Concatenate all files generated by geninfo to a single file per target.
  set(OUTFILE "${LCOV_DATA_PATH_CAPTURE}/${TARGET_NAME}.info")
  lcov_merge_files(OUTFILE "${OUTFILE}" FILES ${GENINFO_FILES})
  add_custom_target(${TARGET_NAME}-geninfo DEPENDS ${OUTFILE})

  # add geninfo file generation to global lcov-capture target
  add_dependencies(lcov-capture ${TARGET_NAME}-geninfo)
  set_property(GLOBAL APPEND PROPERTY LCOV_CAPTURE_FILES "${OUTFILE}")

  # Add target for generating html output for this target only.
  file(MAKE_DIRECTORY ${LCOV_HTML_PATH}/${TARGET_NAME})
  add_custom_target(
    ${TARGET_NAME}-genhtml
    COMMAND
      ${GENHTML_EXE} -q --sort -p ${PROJECT_SOURCE_DIR} -b
      ${LCOV_DATA_PATH_INIT}/${TARGET_NAME}.info -o
      ${LCOV_HTML_PATH}/${TARGET_NAME} -t
      "${CMAKE_PROJECT_NAME} - target ${TARGET_NAME}" ${GENHTML_CPPFILT_FLAG}
      ${OUTFILE}
    DEPENDS ${TARGET_NAME}-geninfo ${TARGET_NAME}-capture-init
    COMMENT "Generating coverage report for target ${TARGET_NAME}")
endfunction()

# Generate the global info file for all targets.
#
# ~~~
# It has to be called after all other CMake functions in the root CMakeLists.txt
# file, to get a full list of all targets that generate coverage data.
# ~~~
function(lcov_capture)
  # Skip this function (and do not create the following targets), if there are
  # no input files.
  get_property(LCOV_CAPTURE_FILES GLOBAL PROPERTY LCOV_CAPTURE_FILES)
  if("${LCOV_CAPTURE_FILES}" STREQUAL "")
    return()
  endif()

  # Add a new target to merge the files of all targets.
  set(OUTFILE "${LCOV_DATA_PATH_CAPTURE}/all-targets.info")
  lcov_merge_files(OUTFILE "${OUTFILE}" FILES ${LCOV_CAPTURE_FILES})

  add_custom_target(
    lcov-geninfo
    DEPENDS ${OUTFILE} lcov-capture
    COMMENT "Capturing global coverage data")

  # Add a new global target for all lcov targets. This target could be used to
  # generate the lcov html output for the whole project instead of calling
  # <TARGET>-geninfo and <TARGET>-genhtml for each target. It will also be used
  # to generate a html site for all project data together instead of one for
  # each target.
  if(NOT TARGET lcov)
    file(MAKE_DIRECTORY ${LCOV_HTML_PATH}/all-targets)
    add_custom_target(
      lcov
      COMMAND
        ${GENHTML_EXE} -q --sort -b ${LCOV_DATA_PATH_INIT}/all-targets.info -o
        ${LCOV_HTML_PATH}/all-targets --title "${CMAKE_PROJECT_NAME}" -p
        "${PROJECT_SOURCE_DIR}" ${GENHTML_CPPFILT_FLAG} ${OUTFILE}
      DEPENDS lcov-geninfo-init lcov-geninfo
      COMMENT "Generating global coverage report")

    add_custom_command(
      TARGET lcov
      POST_BUILD
      COMMAND ;
      COMMENT
        "Open file://${LCOV_HTML_PATH}/all-targets/index.html in your browser to view the coverage report."
    )
  endif()
endfunction()

# Add a new global target to generate the lcov html report for the whole project
# instead of calling <TARGET>-genhtml for each target (to create an own report
# for each target). Instead of the lcov target it does not require geninfo for
# all targets, so you have to call <TARGET>-geninfo to generate the info files
# the targets you'd like to have in your report or lcov-geninfo for generating
# info files for all targets before calling lcov-genhtml.
file(MAKE_DIRECTORY ${LCOV_HTML_PATH}/selected-targets)
if(NOT TARGET lcov-genhtml)

  # TODO(klay): Make it better
  add_custom_target(
    lcov-genhtml
    COMMAND
      ${GENHTML_EXE} --quiet --output-directory
      ${LCOV_HTML_PATH}/selected-targets --title \"${CMAKE_PROJECT_NAME} -
      targets `find ${LCOV_DATA_PATH_CAPTURE} -name '*.info' ! -name
      'all-targets.info'`-exec basename {} .info \\\;\" --prefix
      ${PROJECT_SOURCE_DIR} --sort ${GENHTML_CPPFILT_FLAG} `find
      ${LCOV_DATA_PATH_CAPTURE} -name '*.info' ! -name 'all-targets.info'`)
endif()
