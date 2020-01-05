# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

include(GoogleTest)

add_subdirectory(Commands)

file(GLOB CONSOLE_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(ConsoleTest ${ZEPHIR_TESTS_SOURCE_DIR}/main.cpp ${CONSOLE_TESTS})

target_include_directories(
        ConsoleTest
        PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE $<BUILD_INTERFACE:${ZEPHIR_TESTS_SOURCE_DIR}>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

target_link_libraries(ConsoleTest PRIVATE console CONAN_PKG::GTest)

gtest_discover_tests(
        ConsoleTest
        TEST_PREFIX zephir:
        PROPERTIES LABELS ConsoleTest)

set_property(GLOBAL APPEND PROPERTY ZEPHIR_TESTS ConsoleTest)
