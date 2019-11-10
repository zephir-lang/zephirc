cmake_minimum_required(VERSION 3.10)
project(spdlog)

# Library
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
