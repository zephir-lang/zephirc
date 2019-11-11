# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

# Install SpdLog as static library before using it.
if(UNIX)
  find_library(
    SPDLOG_LIBRARY
    NAMES libspdlog PATH $ENV{SPDLOG_DIR} /usr/local/lib /opt
    DOC "path to spdlog pre-compiled library")
elseif(WIN32)
  find_library(
    SPDLOG_LIBRARY
    NAMES libspdlog PATH $ENV{SPDLOG_DIR} C:/
    DOC "path to spdlog pre-compiled library")
endif()

message(STATUS "Check for spdlog library: ${SPDLOG_LIBRARY}")
