<p align="center"><a href="https://zephir-lang.com" target="_blank">
    <img src="https://assets.phalconphp.com/zephir/zephir_logo-105x36.svg" height="100" alt="Zephir"/>
</a></p>

[Zephir][0] - is a high level programming language that eases the creation and maintainability of extensions for PHP.
Zephir extensions are exported to C code that can be compiled and optimized by major C compilers such as gcc/clang/vc++.
Functionality is exposed to the PHP language.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

#### POSIX

- [cmake](https://cmake.org/) >= 3.10
- [gcc](https://gcc.gnu.org) >= 5.0.0 or [clang](https://clang.llvm.org) >= 3.6.0

### Building from Source

#### POSIX

```shell script
cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Running the tests

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
3. Call `make ccov-all` inside the `build` direcory

## License

Zephir licensed under the MIT License. See the [LICENSE][8] file for more information.

[0]: https://zephir-lang.com
[8]: https://github.com/phalcon/zephir/blob/master/LICENSE
