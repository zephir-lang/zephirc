# This file is part of the Zephir.
#
# (c) Phalcon Team <team@zephir-lang.com>
# (c) 2018 George Cave <gcave@stablecoder.ca>
#
# For the full copyright and license information, please view
# the LICENSE file that was distributed with this source code.

option(ENABLE_ALL_WARNINGS "Compile with all warnings for the major compilers"
       OFF)
option(ENABLE_EFFECTIVE_CXX "Enable Effective C++ warnings" OFF)
option(GENERATE_DEPENDENCY_DATA "Generates .d files with header dependencies"
       OFF)

if(ENABLE_ALL_WARNINGS)
  if(CMAKE_COMPILER_IS_GNUCC
     OR CMAKE_COMPILER_IS_GNUCXX
     OR CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang"
     OR CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
    # GCC/Clang
    add_compile_options(-Wall -Wextra)
  elseif(MSVC)
    # MSVC
    add_compile_options(/W4)
  endif()
endif()

if(ENABLE_EFFECTIVE_CXX)
  if(CMAKE_COMPILER_IS_GNUCC
     OR CMAKE_COMPILER_IS_GNUCXX
     OR CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang"
     OR CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
  endif()
endif()

if(GENERATE_DEPENDENCY_DATA)
  if(CMAKE_COMPILER_IS_GNUCC
     OR CMAKE_COMPILER_IS_GNUCXX
     OR CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang"
     OR CMAKE_CXX_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
    add_compile_options(-MD)
  else()
    message(
      WARNING "Cannot generate header dependency on non GCC/Clang compilers.")
  endif()
endif()
