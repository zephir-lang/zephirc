# If cppcheck is installed, create a target
# to run it on the project source files.
if(UNIX)
  find_program(CPPCHECK_EXECUTABLE
               NAMES cppcheck
               PATHS $ENV{CPPCHECK_DIR}
                     /usr
                     /usr/local
                     /opt
                     /opt/local
               PATH_SUFFIXES bin
               DOC "path to the cppcheck executable")
elseif(WIN32)
  find_program(CPPCHECK_EXECUTABLE
               NAMES cppcheck.exe
               PATHS $ENV{CPPCHECK_DIR} C:/
               PATH_SUFFIXES ""
               DOC "path to the cppcheck executable")
endif()

mark_as_advanced(CPPCHECK_EXECUTABLE)

if(CPPCHECK_EXECUTABLE)
    message(STATUS "Looking for cppcheck... ${CPPCHECK_EXECUTABLE}")
    add_custom_target(cppcheck
        COMMAND "${CPPCHECK_EXECUTABLE}"
                --quiet
                --error-exitcode=1
                --enable=warning,portability,performance,style
                --language=c++
                "--std=c++${CMAKE_CXX_STANDARD}"
                "--suppress=*:${CMAKE_SOURCE_DIR}/src/commands/scanner.cpp"
                "${CMAKE_SOURCE_DIR}/src")
else()
    message(STATUS "Looking for cppcheck... NOT FOUND")
endif()
