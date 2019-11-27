# Internals

The purpose of this document is to explain how Zephir is built internally.
If you're interested in helping to improve Zephir, this is the information
you need.

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
