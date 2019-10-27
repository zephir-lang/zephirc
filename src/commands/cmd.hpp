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
struct BuilCmd {};

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

class Cmd {
 public:
  // what kind of command
  CmdKind kind;

  // command-specific options
  union {
    ApiCmd api;
    BuilCmd build;
    CleanCmd clean;
    FullcleanCmd fullclean;
    GenerateCmd generate;
    HelpCmd help;
    InitCmd init;
    InstallCmd install;
    StubsCmd stubs;
  };

  // common options
  struct {
    bool quiet;
    bool common_help;
    bool version;
    bool vernum;
    bool dumpversion;
  };
};

bool parseopt(char **argv, Cmd &cmd);
}  // namespace commands

#endif  // ZEPHIR_COMMANDS_CMD_HPP_
