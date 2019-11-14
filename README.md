<p align="center"><a href="https://zephir-lang.com" target="_blank">
    <img src="https://assets.phalconphp.com/zephir/zephir_logo-105x36.svg" height="100" alt="Zephir"/>
</a></p>

[Zephir][0] - is a high level programming language that eases the creation and maintainability of extensions for PHP.
Zephir extensions are exported to C code that can be compiled and optimized by major C compilers such as gcc/clang/vc++.
Functionality is exposed to the PHP language.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

To build Zephir compiler you need the following requirements:

#### POSIX

- A C compiler such as  [gcc](https://gcc.gnu.org) >= 7.0.0 or [clang](https://clang.llvm.org) >= 4.0.0
- [cmake](https://cmake.org/) 3.11 or later
- Library for easy read/write for Yaml data: [yaml-cpp](https://github.com/jbeder/yaml-cpp) >= 0.6
- Library for logging: [spdlog](https://github.com/gabime/spdlog) >= 1.4
- Python 3 (Optional: To use [`cmake-format`](https://github.com/cheshirekow/cmake_format))
- C++ language standard support: C++17

If you're using Ubuntu, you can install the required packages this way:

```shell script
# on Ubuntu libspdlog-dev is available from 16.04
sudo apt-get install gcc cmake libyaml-cpp-dev build-essential libspdlog-dev
```

On macOS you will need to use brew with a command as follows:
```shell script
brew install cmake yaml-cpp spdlog
```

Please note that specific versions of libraries and programs at the time of reading this guide may vary.

### Building from Source

#### POSIX

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

cd build
make
ctest
```

### Additional cmake flags

Additional cmake flags are (e.g. to enable `FEATURE` use `-DFEATURE=ON`):

| Description                                         | Flag                   |
| --------------------------------------------------- |------------------------|
| Generate code coverage report.                      | `CODE_COVERAGE`        |
| Compile with all warnings for the major compilers.  | `ENABLE_ALL_WARNINGS`  |
| Enable Effective C++ warnings.                      | `ENABLE_EFFECTIVE_CXX` |

### Generate HTML code coverage report

1. Build project using `-DCODE_COVERAGE=ON`
2. Run tests
3. Call `make ccov-all` inside the `build` directory

## Internals

#### Library dependencies graph

```
.
└── zephir
    ├── commands
    ├── config
    │   └── filesystem
    │   └── yaml-cpp
    └── filesystem
```

## License

Zephir licensed under the MIT License. See the [LICENSE][8] file for more information.

[0]: https://zephir-lang.com
[8]: https://github.com/phalcon/zephir/blob/master/LICENSE
