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

# Set the compiler standard to C++11
macro(cxx_11)
  message(STATUS "Set the compiler standard to C++11")

  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

# Set the compiler standard to C++14
macro(cxx_14)
  message(STATUS "Set the compiler standard to C++14")

  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

# Set the compiler standard to C++17
macro(cxx_17)
  message(STATUS "Set the compiler standard to C++17")

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

# Set the compiler standard to C++20
macro(cxx_20)
  message(STATUS "Set the compiler standard to C++20")

  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

# c++-standards.cmake ends here

# cmake-format: off
# Local Variables:
# mode: cmake
# tab-width: 4
# indent-tabs-mode: nil
# End:
# cmake-format: on
