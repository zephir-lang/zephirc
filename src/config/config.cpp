// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config.hpp"

#include <yaml-cpp/yaml.h>

#include "commands/commands.hpp"
#include "filesystem/filesystem.hpp"
#include "zephir/main.hpp"

namespace {
int parse_yaml_config(zephir::Config *config, const std::string &config_file) {
  if (!zephir::filesystem::exists(config_file)) {
    // Do nothing.
    return EXIT_NO_CONFIG;
  }

  // BadFile should normally never thrown.
  // We did check for file existence before.
  try {
    YAML::Node loaded_config = YAML::LoadFile(config_file);
  } catch (YAML::ParserException &e) {
    // TODO(klay): Probable we need to notify user about broken config file
    return EXIT_BAD_CONFIG;
  }

  // TODO(klay): Implement me.
  return 0;
}
}  // namespace

zephir::Config::Config() {
  container.api.theme.options["github"] = "";
  container.api.theme.options["analytics"] = "";
  container.api.theme.options["main_color"] = "#3E6496";
  container.api.theme.options["link_color"] = "#3E6496";
  container.api.theme.options["link_hover_color"] = "#5F9AE7";
}

zephir::Config zephir::load_config(int argc, char **argv,
                                   const std::string &config_file) {
  zephir::Config config;
  auto retval = zephir::commands::optparse(argc, argv);
  if (retval == EXIT_HELP) {
    // Do nothing on "zephir --help" command.
    return config;
  }

  if (retval != 0) {
    // TODO(klay): Throw exception. Args related?
  }

  if (!config_file.empty()) {
    retval = parse_yaml_config(&config, config_file);
    switch (retval) {
      case 0:
      // Nothing to do if we unable to find config file at the disk.
      case EXIT_NO_CONFIG:
        break;
      default:
        // TODO(klay): Throw exception. Config is broken?
        break;
    }
  }

  return config;
}
