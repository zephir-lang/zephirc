find_package(Criterion REQUIRED)

file(GLOB UNIT_TEST_SOURCE_LIST ./*.test.cpp)

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        argv.cpp
        ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
        PUBLIC commands
        PUBLIC ${CRITERION_LIBRARIES})

target_include_directories(${TARGET_NAME}
        PUBLIC ${CRITERION_INCLUDE_DIR})

# configure unit tests via CTest
add_test(
        NAME RunTests
        COMMAND $<TARGET_FILE:${TARGET_NAME}>)
