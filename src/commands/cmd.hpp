// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_HPP_
#define ZEPHIR_COMMANDS_CMD_HPP_

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
struct ApiCmd {
  const char *backend;
  const char *path;
  const char *output;
  const char *options;
  const char *url;
  bool help;
};

// build-specific options
struct BuildCmd {};

// clean-specific options
struct CleanCmd {};

// fullclean-specific options
struct FullcleanCmd {};

// generate-specific options
struct GenerateCmd {};

// help-specific options
struct HelpCmd {};

// init-specific options
struct InitCmd {};

// install-specific options
struct InstallCmd {};

// stubs-specific options
struct StubsCmd {};

// common options
struct CommonOpts {
  bool quiet;
  bool help;
  bool version;
  bool vernum;
  bool dumpversion;
};

class Cmd {
 public:
  // what kind of command
  CmdKind kind;

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
};
}  // namespace commands

#endif  // ZEPHIR_COMMANDS_CMD_HPP_
