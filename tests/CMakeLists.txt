# This file is part of the Zephir.
#
# (c) Zephir Team <team@zephir-lang.com>
#
# For the full copyright and license information, please view the LICENSE file
# that was distributed with this source code.

include(install-gtest)
include(GoogleTest)

set(ZEPHIR_TESTS options_test config_test)
mark_as_advanced(ZEPHIR_TESTS)

file(GLOB TESTSF ${CMAKE_CURRENT_SOURCE_DIR}/commands/*.options.cpp)
add_executable(options_test main.cpp argv.cpp env/base.cpp ${TESTSF})

target_include_directories(
  options_test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          ${CMAKE_SOURCE_DIR}/src/commands)

target_link_libraries(options_test PRIVATE gtest PUBLIC commands)
#target_code_coverage(options_test
#        AUTO ALL EXCLUDE ${COVERAGE_EXCLUDES}
#        OBJECTS commands)

gtest_discover_tests(
  options_test
  TEST_PREFIX gtest:
  PROPERTIES LABELS OptionsTest)

file(GLOB TESTSF ${CMAKE_CURRENT_SOURCE_DIR}/config/*.cpp)
add_executable(config_test main.cpp argv.cpp env/base.cpp ${TESTSF})

target_include_directories(
  config_test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
          $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
          ${CMAKE_SOURCE_DIR}/src/config)

target_link_libraries(config_test PRIVATE gtest PUBLIC config)
#target_code_coverage(config_test
#        AUTO ALL EXCLUDE ${COVERAGE_EXCLUDES}
#        OBJECTS config)

gtest_discover_tests(
  config_test
  TEST_PREFIX gtest:
  PROPERTIES LABELS ConfigTest)

# Handle codecoverage
if(CODE_COVERAGE)
    include(CodeCoverage)

    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage" PARENT_SCOPE)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage" PARENT_SCOPE)
    # APPEND_COVERAGE_COMPILER_FLAGS

    #"/usr/*"
    #"build/*"
    #"*/build/*"
    #"tests/*"
    #"*/tests/*"
    #"external/*"
    #"*/external/*"

    # append_coverage_compiler_flags()

    set(COVERAGE_EXCLUDES '/usr/*' '*/build/*' '*/usr/include/*' '*/tests/*' '*/external/*')

    setup_code_coverage_target(
            NAME check
            EXECUTABLE ctest -j ${BUILD_JOBS} --output-on-failure
            DEPENDENCIES ${ZEPHIR_TESTS})
endif()

# cmake-format: off
# TODO: sharness tests
# if(NOT WIN32)
#     add_test(
#     NAME              BlackboxTest
#     COMMAND           make
#     WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sharness")
# endif()
# cmake-format: on

# CMakeLists.txt ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
