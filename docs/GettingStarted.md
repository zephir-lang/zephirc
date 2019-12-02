# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites

To build Zephir compiler you need the following requirements:

### POSIX

* A C compiler such as  [Gcc](https://gcc.gnu.org) >= 7.0.0, [Clang](https://clang.llvm.org) >= 5.0.0 or [Apple Clang](https://apps.apple.com/us/app/xcode/id497799835) >= 10.0.0
* [cmake](https://cmake.org/) 3.11 or later
* Library for easy read/write for Yaml data: [yaml-cpp](https://github.com/jbeder/yaml-cpp) >= 0.6
* Library for logging: [spdlog](https://github.com/gabime/spdlog) >= 1.4
* C++ language standard support: C++17

#### Optional

* Static analysis tool for C/C++ code: [Cppcheck](https://github.com/danmar/cppcheck) >= 1.89
* Cmake formatting tool: [cmake-format](https://github.com/cheshirekow/cmake_format)
* C, C++ formatting tool: [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* To enable test coverage reports you need the following requirements:
  * Gcc: `lcov`, `genhtml`
  * Clang, Apple Clang: `llvm-profdata`, `llvm-cov`

If you're using Ubuntu, you can install the required packages this way:

```shell script
# on Ubuntu libspdlog-dev is available from 16.04
sudo apt-get install \
    gcc \
    cmake \
    cppcheck \
    pkg-config \
    build-essential \
    libspdlog-dev \
    libyaml-cpp-dev \
    clang-format
```

On macOS you will need to use brew with a command as follows:
```shell script
brew install \
    cmake \
    cppcheck \
    pkg-config \
    yaml-cpp \
    spdlog \
    clang-format
```

Please note that specific versions of libraries and programs at the time of reading this guide may vary.

## Building from Source

First you need to get initial project:

```shell script
git clone git@github.com:sergeyklay/cpp-zephir.git
cd cpp-zephir
git submodule init
git submodule update
```

And wait for load any required dependencies. The next step is to build project.

### POSIX

```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Running the tests

To run the tests, you have to configure Zephir with special flags:

### POSIX

```shell script
cmake -H. \
  -Bbuild \
  -DCMAKE_BUILD_TYPE=Debug \
  -DZEPHIR_BUILD_TESTING=ON

export ZEPHIR_TESTS_ROOT=$(pwd)/tests

cd build
make
make check
```

Environment variable `ZEPHIR_TESTS_ROOT` is needed for those tests which reads fixture files from the disk.

### Additional cmake flags

Additional cmake flags are (e.g. to enable `FEATURE` use `-DFEATURE=ON`):

| Description                                         | Flag                   |
| --------------------------------------------------- |------------------------|
| Add `cppcheck` step to the compilation.             | `CPPCHECK`             |
| Generate code coverage report.                      | `CODE_COVERAGE`        |
| Compile with all warnings for the major compilers.  | `ENABLE_ALL_WARNINGS`  |
| Enable Effective C++ warnings.                      | `ENABLE_EFFECTIVE_CXX` |

### Generate HTML code coverage report

Follow these steps:

1. Build project using `-DCODE_COVERAGE=ON`
2. Run tests
3. Call `make ccov-all` inside the `build` directory
