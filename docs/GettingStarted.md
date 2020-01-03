## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites

To build Zephir compiler you'll need the following requirements:
* A C++17 compatible compiler such as [Gcc](https://gcc.gnu.org) >= 7.0.0, [Clang](https://clang.llvm.org) >= 5.0.0 or [Apple Clang](https://apps.apple.com/us/app/xcode/id497799835) >= 10.0.0
* [CMake](https://cmake.org) 3.11 or later
* [conan](https://conan.io) decentralized package manager with a client-server architecture

For project dependencies list see `conanfile.txt` bundled with this project.

Optional prerequisites are:
* Static analysis tool for C/C++ code: [Cppcheck](https://github.com/danmar/cppcheck) >= 1.89
* CMake formatting tool: [cmake-format](https://github.com/cheshirekow/cmake_format)
* C, C++ formatting tool: [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* Documentation generation tool: [Doxygen](http://www.doxygen.org)

To enable test coverage reports you need the following requirements:
* `lcov`
* `genhtml`

If you're using Ubuntu, you can install the required packages this way:
```shell script
sudo apt install gcc cmake build-essential
```

On macOS you most likely have a compiler so you'll need only CMake:
```shell script
brew install cmake
```

Please note that specific versions of libraries and programs at the time of reading this guide may vary.
The following dependencies is recommended install using [`pip`](https://pip.pypa.io):
* `conan`
* `cppcheck`
* `cmake-format`
* `clang-format`

They can be installed using pip as follows:
```shell script
pip install -r requirements.txt
```

**Note:** On macOS to install `clang-format` you'll need use `brew`.

And then install project dependencies using `conan` as follows:
```shell script
conan install . -if=$(pwd)/build --build=missing
```

For a detailed instruction on how to use and customize `conan` please refer
[here](https://docs.conan.io/en/latest/getting_started.html).

### Building

First you'll need clone the project and fetch its modules:
```shell script
git clone https://github.com/zephir-lang/zephirc
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

To build with testing support, you have to configure Zephir with special flags:
```shell script
cmake -H. \
  -Bbuild \
  -DCMAKE_BUILD_TYPE=Debug \
  -DZEPHIR_BUILD_TESTING=ON

cmake --build build
```

Run Zephir tests from the project root as follows:
```shell script
cmake --build build --target check
```

## Configure flags

To enable any feature use CMake flags at configure time. To enable `FEATURE` use `-DFEATURE=ON`
and to disable `FEATURE` use `-DFEATURE=OFF`. Supported CMake flags are:

| Flag                   | Description                                             |
| ---------------------- |---------------------------------------------------------|
| `CPPCHECK`             | Add `cppcheck` step to the compilation.                 |
| `CODE_COVERAGE`        | Generate code coverage report.                          |
| `ENABLE_ALL_WARNINGS`  | Compile with all warnings for the major compilers.      |
| `ENABLE_EFFECTIVE_CXX` | Enable Effective C++ warnings.                          |
| `BUILD_DEP_GRAPH`      | Builds a visual representation of the project.          |
| `ZEPHIR_BUILD_DOC`     | ON to generate the API documentation, OFF to ignore it. |

### Generate HTML code coverage report

Follow these steps:
1. Configure with code coverage instrumentation enabled `-DCODE_COVERAGE=ON`
2. Run `./ci/make-test-coverage.sh` from the project root
3. Open `./build/ccov/html/index.html` in your browser to view the coverage report

### Generate the API documentation

Follow these steps:
1. Configure with API docs generations support `-DZEPHIR_BUILD_DOC=ON`
2. Build project
3. Call `cmake --build build --target doc` from the project root directory
