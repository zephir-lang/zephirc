set(TARGET_NAME zephir)

include(CxxFlags)

add_subdirectory(commands)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} commands)
