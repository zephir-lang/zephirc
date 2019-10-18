<p align="center"><a href="https://zephir-lang.com" target="_blank">
    <img src="https://assets.phalconphp.com/zephir/zephir_logo-105x36.svg" height="100" alt="Zephir"/>
</a></p>

[Zephir][0] -  is a high level **Programming Language** that eases the creation and maintainability of extensions for PHP.
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

### Prerequisites

- [Catch2](https://github.com/catchorg/Catch2)

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

## License

Zephir licensed under the MIT License. See the [LICENSE][8] file for more information.

[0]: https://zephir-lang.com
[8]: https://github.com/phalcon/zephir/blob/master/LICENSE
