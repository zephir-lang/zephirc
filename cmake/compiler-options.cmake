# Copyright (C) 2018 by George Cave - gcave@stablecoder.ca
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

option(ENABLE_ALL_WARNINGS "Compile with all warnings for the major compilers."
       OFF)
option(ENABLE_EFFECTIVE_CXX "Enable Effective C++ warnings." OFF)

# TODO(klay): add_definitions(-DZEPHIR_RELEASE)

if(ENABLE_ALL_WARNINGS)
  if(CMAKE_COMPILER_IS_GNUCXX)
    # GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  elseif(CMAKE_COMPILER_IS_CLANG OR CMAKE_COMPILER_IS_APPLE_CLANG)
    # Clang
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  elseif(MSVC)
    # MSVC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

# TODO(klay): We can't apply this on Linux with gtests.
if(ENABLE_EFFECTIVE_CXX)
  if(CMAKE_COMPILER_IS_GNUCXX)
    # GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
  elseif(CMAKE_COMPILER_IS_CLANG OR CMAKE_COMPILER_IS_APPLE_CLANG)
    # Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
  endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# compiler-options.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
