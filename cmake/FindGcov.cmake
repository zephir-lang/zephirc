# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.
#
# Initially written by Alexander Haase <alexander.haase@rwth-aachen.de>
# Adapted by Serghei Iakovlev <egrep@protonmail.ch>

# Include required Modules
include(FindPackageHandleStandardArgs)

get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
foreach(LANG ${ENABLED_LANGUAGES})
  # Gcov evaluation is dependent on the used compiler. Check gcov support for
  # each compiler that is used. If gcov binary was already found for this
  # compiler, do not try to find it again.
  message("   > LANG: ${LANG}")
  message("   > CMAKE_${LANG}_COMPILER_ID: ${CMAKE_${LANG}_COMPILER_ID}")
  message("   > CMAKE_${LANG}_COMPILER: ${CMAKE_${LANG}_COMPILER}")
  message(
    "   > CMAKE_${LANG}_COMPILER_VERSION: ${CMAKE_${LANG}_COMPILER_VERSION}")

  if(NOT GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE)
    get_filename_component(COMPILER_PATH "${CMAKE_${LANG}_COMPILER}" PATH)
    message("   > COMPILER_PATH: ${COMPILER_PATH}")

    if("${CMAKE_${LANG}_COMPILER_ID}" STREQUAL "GNU")
      # Some distributions like OSX (homebrew) ship gcov with the compiler
      # version appended as gcov-x. To find this binary we'll build the
      # suggested binary name with the compiler version.
      string(REGEX MATCH "^[0-9]+" GCC_VERSION
                   "${CMAKE_${LANG}_COMPILER_VERSION}")

      find_program(
        GCOV_EXE
        NAMES gcov-${GCC_VERSION} gcov
        HINTS ${COMPILER_PATH})
      mark_as_advanced(GCOV_EXE)
      message("   > GCOV_EXE: ${GCOV_EXE}")
    elseif("${CMAKE_${LANG}_COMPILER_ID}" STREQUAL "AppleClang")
      # There is nothing special for Apple Clang. Usually "gcov" is a symlink to
      # llvm-cov
      find_program(
        GCOV_EXE
        NAMES gcov llvm-cov
        HINTS ${COMPILER_PATH})
      mark_as_advanced(GCOV_EXE)
      message("   > GCOV_EXE: ${GCOV_EXE}")
    elseif("${CMAKE_${LANG}_COMPILER_ID}" STREQUAL "Clang")
      # Some distributions like Debian ship llvm-cov with the compiler version
      # appended as llvm-cov-x.y. To find this binary we'll build the suggested
      # binary name with the compiler version.
      string(REGEX MATCH "^[0-9]+.[0-9]+" LLVM_VERSION
                   "${CMAKE_${LANG}_COMPILER_VERSION}")

      # llvm-cov prior version 3.5 seems to be not working with coverage
      # evaluation tools, but these versions are compatible with the gcc gcov
      # tool.
      if(LLVM_VERSION VERSION_GREATER 3.4)
        find_program(
          LLVM_COV_EXE
          NAMES llvm-cov-${LLVM_VERSION} llvm-cov
          HINTS ${COMPILER_PATH})
        mark_as_advanced(LLVM_COV_EXE)
        message("   > LLVM_COV_EXE: ${LLVM_COV_EXE}")

        if(LLVM_COV_EXE)
          # TODO(klay): Provide ability to pass wrapper path
          find_program(LLVM_COV_WRAPPER llvm-cov-wrapper
                       PATHS ${CMAKE_MODULE_PATH})
          mark_as_advanced(LLVM_COV_WRAPPER)
          if(LLVM_COV_WRAPPER)
            set(GCOV_EXE
                "${LLVM_COV_WRAPPER}"
                CACHE FILEPATH "")

            # set additional parameters
            set(GCOV_${CMAKE_${LANG}_COMPILER_ID}_ENV
                "LLVM_COV_EXE=${LLVM_COV_EXE}"
                CACHE STRING "Environment variables for llvm-cov-wrapper.")
            mark_as_advanced(GCOV_${CMAKE_${LANG}_COMPILER_ID}_ENV)
            message(
              "   > GCOV_${CMAKE_${LANG}_COMPILER_ID}_ENV: ${GCOV_${CMAKE_${LANG}_COMPILER_ID}_ENV}"
            )
          endif()
        endif()
      endif()

      if(NOT GCOV_EXE)
        # Fall back to gcov binary if llvm-cov was not found or is incompatible.
        # This is the default on OSX, but may crash on recent Linux versions.
        find_program(GCOV_EXE gcov HINTS ${COMPILER_PATH})
        mark_as_advanced(GCOV_EXE)
      endif()
    endif()

    if(GCOV_EXE)
      set(GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE
          "${GCOV_EXE}"
          CACHE STRING "${LANG} gcov binary.")
      message(
        "   > GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE: ${GCOV_${CMAKE_${LANG}_COMPILER_ID}_EXE}"
      )

      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Found gcov evaluation for "
                       "${CMAKE_${LANG}_COMPILER_ID}: ${GCOV_EXE}")
      endif()

      unset(GCOV_EXE CACHE)
    endif()
  endif()
endforeach()

# Add a new global target for all gcov targets. This target could be used to
# generate the gcov files for the whole project instead of calling <TARGET>-gcov
# for each target.
if(NOT TARGET gcov)
  add_custom_target(gcov)
endif()
