find_package(CppUnit REQUIRED)

include_directories(${CPPUNIT_INCLUDE_DIR})

# mirror the filename and path of the unit under test and
# add ".test" suffix
set(UNIT_TEST_LIST
        commands)

foreach(NAME IN LISTS UNIT_TEST_LIST)
    list(APPEND UNIT_TEST_SOURCE_LIST "${NAME}.test.cpp")
endforeach()

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
        main.cpp
        test_helpers.cpp
        ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME}
        PUBLIC commands
        ${CPPUNIT_LIBRARY})

# configure unit tests via CTest
add_test(NAME RunTests COMMAND $<TARGET_FILE:${TARGET_NAME}>)
