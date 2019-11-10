# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

# Downloads SpdLog sources from repository
include(FetchContent)

FetchContent_Declare(spdlog
    PREFIX         spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    # GIT_TAG        v1.4.2
    )

FetchContent_GetProperties(spdlog)

if(NOT spdlog_POPULATED)
    message(STATUS "Downloading SpdLog sources...")
    # TODO: move headers to External
    # set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog)

    FetchContent_Populate(spdlog)

    set(spdlog_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/spdlog-src/include)

    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
endif()

message(STATUS "Found SpdLog Headers: ${spdlog_INCLUDE_DIRS}")

