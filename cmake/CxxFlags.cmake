# RELEASE Flags

# Show all warnings and enable some extra warning flags
if(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang"))
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /W4")
endif()

# Set release veriable todo: add_definitions(-DZEPHIR_RELEASE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DZEPHIR_RELEASE")

# DEBUG Flags

# Forcing the compiler to work harder helps finding potential problems
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# Show all warnings and enable some extra warning flags
if(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang"))
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
endif()

# Warn if anything depends upn the size of a function or of void
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wpointer-arith")

# Avoid int i = i
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Winit-self")

# Dont check floats for equality
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wfloat-equal")

# Warn if an unitialized identifier is evaluated
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wundef")

# Warn whenever a local variable shadows another local/global one
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wshadow")

# Warn if a pointer is cast such that alignment of target is increased
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wcast-align")

# Give string consts the type const char[length}
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wwrite-strings")

# Warn whenever a poinster is cast to remove a type qualifier from target
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wcast-qual")

# Warn whenever a switch does not have a default case
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wswitch-default")

# Warn whenever a switch has an index of enumerated type and lacks a case
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wswitch-enum")

# Warn for implicit conversions that may alter a value
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wconversion")

# Warn ifh the compiler detects code that will never be executed
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wunreachable-code")

# Issue all warnings demanded by strict ISO C++
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pedantic")

# TODO: Move to separated module
if(ZEPHIR_CODE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    # For more see: https://clang.llvm.org/docs/SourceBasedCodeCoverage.html
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    link_libraries(-fprofile-instr-generate -fcoverage-mapping)
    message(STATUS "Code coverage metrics enabled for debug build")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    link_libraries(-fprofile-arcs -ftest-coverage)
    message(STATUS "Code coverage metrics enabled for debug build")
  elseif(MSVC)
    # TODO: what kind of flags are needed to profile on MSVC?
    message(STATUS "Code coverage metrics isn't enabled for debug build")
  endif()
endif()

# CxxFlags.cmake ends here

# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
