# FindRe2c.cmake
#
# Provides a macro to generate custom build rules:
#
#   RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]
#
# which creates a custom commands to generate the <Output> file from
# the <Input> file. If COMPILE_FLAGS option is specified, the next
# parameter is added to the re2c commands line. Name is an alias used to
# get details of this custom commands.
#
# Example:
#
#   find_package(Re2c)
#
#   RE2C_TARGET(MyScanner
#       scanner.re
#       "${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp"
#       COMPILE_FLAGS "-W"
#   )
#
#   include_directories("${CMAKE_CURRENT_BINARY_DIR}")
#
#   add_library(MyScanner scanner.hpp "${RE2C_MyScanner_OUTPUTS}")
#
#   add_executable(Foo Foo.cpp)
#   target_link_libraries(Foo
#           PRIVATE MyScanner)
#
# The module defines the following variables:
#
#   RE2C_EXECUTABLE - the path to the re2c executable
#   RE2C_VERSION    - version of the re2c

if (UNIX)
    find_program(RE2C_EXECUTABLE
            NAMES re2c
            PATHS $ENV{RE2C_DIR} /usr /usr/local /opt /opt/local
            PATH_SUFFIXES re2c/bin bin
            DOC "path to the re2c executable")
elseif (WIN32)
    find_program(RE2C_EXECUTABLE
            NAMES re2c.exe
            PATHS $ENV{RE2C_DIR} C:/
            PATH_SUFFIXES re2c/bin bin
            DOC "path to the re2c executable")
endif ()

set(RE2C_VERSION "")

mark_as_advanced(RE2C_EXECUTABLE)

if (RE2C_EXECUTABLE)
    execute_process(
            COMMAND ${RE2C_EXECUTABLE} --version
            RESULT_VARIABLE RE2C_VERSION_RESULT
            OUTPUT_VARIABLE RE2C_VERSION_OUTPUT
            ERROR_VARIABLE RE2C_VERSION_ERROR
            OUTPUT_STRIP_TRAILING_WHITESPACE)

    string(REGEX REPLACE "^re2c " "" RE2C_VERSION_OUTPUT "${RE2C_VERSION_OUTPUT}")

    if (RE2C_VERSION_RESULT EQUAL 0)
        set(RE2C_VERSION ${RE2C_VERSION_OUTPUT})
    else ()
        message(SEND_ERROR
                "Command \"${RE2C_EXECUTABLE} --version\" failed with output:\n${RE2C_VERSION_ERROR}")
    endif ()

    # RE2C_TARGET (public macro)
    # TODO - rework this macro to make use of CMakeParseArguments, see
    # http://www.cmake.org/pipermail/cmake/2012-July/051309.html
    if (NOT COMMAND RE2C_TARGET)
        macro(RE2C_TARGET Name Input Output)
            set(RE2C_TARGET_USAGE "RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]")
            if (${ARGC} GREATER 3)
                if (${ARGC} EQUAL 5)
                    if ("${ARGV3}" STREQUAL "COMPILE_FLAGS")
                        set(RE2C_EXECUTABLE_OPTS "${ARGV4}")
                        SEPARATE_ARGUMENTS(RE2C_EXECUTABLE_OPTS)
                    else ()
                        message(SEND_ERROR ${RE2C_TARGET_USAGE})
                    endif ()
                else ()
                    message(SEND_ERROR ${RE2C_TARGET_USAGE})
                endif ()
            endif ()

            add_custom_command(OUTPUT ${Output}
                    COMMAND ${RE2C_EXECUTABLE}
                    ARGS ${RE2C_EXECUTABLE_OPTS} -o${Output} ${Input}
                    DEPENDS ${Input} ${RE2C_EXECUTABLE_TARGET}
                    COMMENT "[RE2C][${Name}] Building scanner with ${RE2C_EXECUTABLE} v${RE2C_VERSION}"
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

            set(RE2C_${Name}_DEFINED TRUE)
            set(RE2C_${Name}_OUTPUTS ${Output})
            set(RE2C_${Name}_INPUT ${Input})
            set(RE2C_${Name}_COMPILE_FLAGS ${RE2C_EXECUTABLE_OPTS})

            set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${Output}")
        endmacro()
    endif ()
endif ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
        RE2C
        "No re2c found in the $PATH. Consider install re2c or/and add re2c executable to the $PATH"
        RE2C_EXECUTABLE)

mark_as_advanced(RE2C_VERSION)

# FindRe2c.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
