set(TARGET_NAME zephir)

include(CxxFlags)

add_subdirectory(commands)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} commands)

# CMakeLists.txt ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
