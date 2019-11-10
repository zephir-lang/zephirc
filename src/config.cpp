// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config.hpp"

#include <yaml-cpp/yaml.h>

#include "commands/commands.hpp"

namespace {
void parse_yaml_config(core::Config *config, const std::string &config_file) {
  // TODO(klay): Implement me.
}
}  // namespace

int core::load_config(core::Config *config, int argc, char **argv,
                      std::string config_file) {
  auto retval = commands::optparse(argc, argv);
  if (retval == ZEPHIR_COMMANDS_EXIT_HELP) {
    retval = 0;
  }

  if (!config_file.empty()) {
    parse_yaml_config(config, config_file);
  }

  return retval;
}
