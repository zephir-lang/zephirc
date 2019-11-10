cmake_minimum_required(VERSION 3.10)
project(SpdLog)

# Library
add_library(SpdLog INTERFACE)
target_include_directories(SpdLog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

find_path(SPDLOG_INCLUDE_DIR
  NAMES spdlog/spdlog.h
  HINTS ${CMAKE_CURRENT_SOURCE_DIR}
)

set(spdlog_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR})

message(STATUS "Found SpdLog Headers: ${spdlog_INCLUDE_DIRS}")

