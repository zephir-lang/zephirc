// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_PARSE_RESULT_HPP_
#define ZEPHIR_COMMANDS_PARSE_RESULT_HPP_

namespace commands {

enum class CmdKind {
  NONE = 0,
  API,
  BUILD,
  CLEAN,
  FULLCLEAN,
  GENERATE,
  HELP,
  INIT,
  INSTALL,
  STUBS
};

// api-specific options
class ApiCmd {
 public:
  ApiCmd()
      : backend(""), path(""), output(""), options(""), url(""), help(false) {}
  const char *backend;
  const char *path;
  const char *output;
  const char *options;
  const char *url;
  bool help;
};

// build-specific options
class BuildCmd {};

// clean-specific options
class CleanCmd {};

// fullclean-specific options
class FullcleanCmd {};

// generate-specific options
class GenerateCmd {};

// help-specific options
class HelpCmd {};

// init-specific options
class InitCmd {
 public:
  InitCmd() : backend(""), ns(""), help(false) {}
  const char *backend;
  const char *ns;
  bool help;
};

// install-specific options
class InstallCmd {};

// stubs-specific options
class StubsCmd {};

// common options
class CommonOpts {
 public:
  CommonOpts()
      : quiet(false),
        help(false),
        version(false),
        vernum(false),
        dumpversion(false) {}
  bool quiet;
  bool help;
  bool version;
  bool vernum;
  bool dumpversion;
};

class ParseResult {
 public:
  ParseResult() : common(), kind(CmdKind::NONE) {}
  CmdKind get_kind() const { return kind; }
  void set_kind(const CmdKind cmd_kind) { kind = cmd_kind; }

  // command-specific options
  union {
    ApiCmd api;
    BuildCmd build;
    CleanCmd clean;
    FullcleanCmd fullclean;
    GenerateCmd generate;
    HelpCmd help;
    InitCmd init;
    InstallCmd install;
    StubsCmd stubs;
  };

  CommonOpts common;

 private:
  // what kind of command
  CmdKind kind;
};
}  // namespace commands

#endif  // ZEPHIR_COMMANDS_PARSE_RESULT_HPP_
