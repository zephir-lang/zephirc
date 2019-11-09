#include "zephir/config.hpp"
#include "commands/commands.hpp"

int core::load_config(core::Config *config, int argc, char **argv, std::string config_file) {
  auto retval = commands::optparse(argc, argv);
  if (retval == ZEPHIR_COMMANDS_EXIT_HELP) {
    retval = 0;
  }

  return retval;
}
