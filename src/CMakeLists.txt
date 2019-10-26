include(CxxFlags)

add_subdirectory(commands)

add_executable(zephir main.cpp)
target_link_libraries(zephir commands)

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
