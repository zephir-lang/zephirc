#=============================================================================
# Copyright (c) 2010-2016 United States Government as represented by
#                the U.S. Army Research Laboratory.
# Copyright 2009 Kitware, Inc.
# Copyright 2006 Tristan Carel
# Copyright 2019 Serghei Iakovlev
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
#
# * The names of the authors may not be used to endorse or promote
#   products derived from this software without specific prior written
#   permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# Provides a macro to generate custom build rules:
#
#   RE2C_TARGET(Name RE2CInput RE2COutput [COMPILE_FLAGS <string>])
#
# which creates a custom command  to generate the <RE2COutput> file from
# the <RE2CInput> file.  If  COMPILE_FLAGS option is specified, the next
# parameter is added to the re2c  command line. Name is an alias used to
# get  details of  this custom  command.
#
# Example:
#
#   find_package(RE2C)
#
#   RE2C_TARGET(MyScanner
#       scanner.re
#       "${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp"
#       COMPILE_FLAGS "-W"
#   )
#
#   include_directories("${CMAKE_CURRENT_BINARY_DIR}")
#
#   add_library(MyScanner scanner.hpp "${RE2C_command_OUTPUTS}")
#   add_executable(Foo Foo.cpp)
#   target_link_libraries(Foo MyScanner)
#
# The module defines the following variables:
#
#   RE2C_EXECUTABLE - the path to the re2c executable

find_program(
        RE2C_EXECUTABLE re2c
        DOC "path to the re2c executable"
        PATHS /usr /usr/local /opt /opt/local $ENV{RE2C_DIR}
        PATH_SUFFIXES re2c/bin bin
)

mark_as_advanced(RE2C_EXECUTABLE)

if (RE2C_EXECUTABLE)
    # RE2C_TARGET (public macro)
    # TODO - rework this macro to make use of CMakeParseArguments, see
    # http://www.cmake.org/pipermail/cmake/2012-July/051309.html
    if(NOT COMMAND RE2C_TARGET)
        macro(RE2C_TARGET Name Input Output)
            set(RE2C_TARGET_usage "RE2C_TARGET(<Name> <Input> <Output> [COMPILE_FLAGS <string>]")
            if(${ARGC} GREATER 3)
                if(${ARGC} EQUAL 5)
                    if("${ARGV3}" STREQUAL "COMPILE_FLAGS")
                        set(RE2C_EXECUTABLE_opts  "${ARGV4}")
                        SEPARATE_ARGUMENTS(RE2C_EXECUTABLE_opts)
                    else()
                        message(SEND_ERROR ${RE2C_TARGET_usage})
                    endif()
                else()
                    message(SEND_ERROR ${RE2C_TARGET_usage})
                endif()
            endif()

            add_custom_command(OUTPUT ${Output}
                    COMMAND ${RE2C_EXECUTABLE}
                    ARGS ${RE2C_EXECUTABLE_opts} -o${Output} ${Input}
                    DEPENDS ${Input} ${RE2C_EXECUTABLE_TARGET}
                    COMMENT "[RE2C][${Name}] Building scanner with ${RE2C_EXECUTABLE}"
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

            set(RE2C_${Name}_DEFINED TRUE)
            set(RE2C_${Name}_OUTPUTS ${Output})
            set(RE2C_${Name}_INPUT ${Input})
            set(RE2C_${Name}_COMPILE_FLAGS ${RE2C_EXECUTABLE_opts})
            set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${Output}")
        endmacro(RE2C_TARGET)
    endif(NOT COMMAND RE2C_TARGET)
endif(RE2C_EXECUTABLE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RE2C DEFAULT_MSG RE2C_EXECUTABLE)

# FindRE2C.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
