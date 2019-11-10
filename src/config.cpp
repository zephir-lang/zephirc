// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "commands/commands.hpp"
#include "zephir/config.hpp"

int core::load_config(core::Config *config, int argc, char **argv,
                      std::string config_file) {
  auto retval = commands::optparse(argc, argv);
  if (retval == ZEPHIR_COMMANDS_EXIT_HELP) {
    retval = 0;
  }

  return retval;
}
