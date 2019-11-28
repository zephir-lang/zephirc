# Internals

The purpose of this document is to explain how Zephir is built internally.
If you're interested in helping to improve Zephir, this is the information
you need.

## Conventions

### Naming

The most important consistency rules are those that govern naming.
This Project uses [Google Style](https://google.github.io/styleguide/cppguide.html#Naming).

### CMake

1. Do no use `$ENV{VAR_NAME}`, prefer `-DVAR_NAME[=VALUE]`.

## Entrypoint

Current flow design:

```c++
/* 1. */ auto cmd = zephir::command::CreateFromArgv(argc, argv);
         /* 1a. */ auto cwd = zephir::filesystem::GetCurrentWorkingPath();
         /* 1b. */ auto config = zephir::Config::CreateFromArgv(argc, argv, cwd);
/* 2. */ auto retval = cmd.Execute();
         /* 2a. */ zephir::compiler::CommandName();
/* 3. */ return retval;
```

Legend:

- **`1..9`**   Should be invoked from `main.cpp`
- **`1a..1z`** Should be invoked from `command::CreateFromArgv`
- **`2a..2z`** Should be invoked from `cmd.Execute`

## Dependency graph

```
.
└── zephir
    ├── config
    │   ├── commands
    │   │   └── CLI11
    │   ├── filesystem
    │   └── yaml-cpp
    └── filesystem
```
