find_package(Catch2 REQUIRED)

file(GLOB UNIT_TEST_SOURCE_LIST ./*.test.cpp)

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        main.cpp
        argv.cpp
        ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
        PUBLIC commands
        PUBLIC Catch2::Catch2)

# configure unit tests via CTest
add_test(
        NAME RunTests
        COMMAND $<TARGET_FILE:${TARGET_NAME}>)
