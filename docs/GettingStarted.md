# Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites

To build Zephir compiler you need the following requirements:

* A C compiler such as  [Gcc](https://gcc.gnu.org) >= 7.0.0, [Clang](https://clang.llvm.org) >= 5.0.0 or [Apple Clang](https://apps.apple.com/us/app/xcode/id497799835) >= 10.0.0
* [cmake](https://cmake.org/) 3.11 or later
* [conan](https://conan.io) decentralized package manager with a client-server architecture
* Library for easy read/write for Yaml data: [yaml-cpp](https://github.com/jbeder/yaml-cpp) >= 0.6
* C++ language standard support: C++17

For the full dependency list see `conanfile.txt` file located in the sources root.

### Optional

* Static analysis tool for C/C++ code: [Cppcheck](https://github.com/danmar/cppcheck) >= 1.89
* Cmake formatting tool: [cmake-format](https://github.com/cheshirekow/cmake_format)
* C, C++ formatting tool: [clang-format](https://clang.llvm.org/docs/ClangFormat.html)

To enable test coverage reports you need the following requirements:
* Gcc: `lcov`, `genhtml`
* Clang, Apple Clang: `llvm-profdata`, `llvm-cov`

If you're using Ubuntu, you can install the required packages this way:

```shell script
# on Ubuntu libspdlog-dev is available from 16.04
sudo apt-get install \
    gcc \
    cmake \
    pkg-config \
    build-essential \
    libyaml-cpp-dev \
    clang-format
```

On macOS you will need to use brew with a command as follows:
```shell script
brew install \
    cmake \
    pkg-config \
    yaml-cpp \
    clang-format
```

Please note that specific versions of libraries and programs at the time of reading this guide may vary.
The following dependencies is recommended install using [`pip`](https://pip.pypa.io):

* `conan`
* `cppcheck`
* `cmake-format`

They can be installed using pip as follows:

```shell script
pip install --upgrade conan cppcheck cmake-format
```

## Building from source

First you'll need clone the project and fetch its modules:

```shell script
git clone git@github.com:sergeyklay/cpp-zephir.git
cd cpp-zephir
git submodule init
git submodule update
```

And wait for load any required dependencies. For git 1.6.1 or above you can use something similar to command bellow
to pull latest of all submodules:

```shell script
git submodule update --remote --merge
```

Finally build project as follows:

```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Running the tests

To run the tests, you have to configure Zephir with special flags:

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

Environment variable `ZEPHIR_TESTS_ROOT` is needed for the tests which use fixture files.

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
