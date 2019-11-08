cmake_minimum_required(VERSION 3.10)
project(CLI11)

# Library
add_library(CLI11 INTERFACE)
target_include_directories(CLI11 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
