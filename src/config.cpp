// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config.hpp"

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

  try {
    YAML::Node loaded_config = YAML::LoadFile(config_file);
  } catch (YAML::BadFile &e) {
    // Do nothing.
    return EXIT_NO_CONFIG;
  } catch (YAML::ParserException &e) {
    // TODO(klay): Probable we need to notify user about broken config file
    return EXIT_BAD_CONFIG;
  }

  // TODO(klay): Implement me.
  return 0;
}
}  // namespace

zephir::Config zephir::load_config(int argc, char **argv, std::string config_file) {
  zephir::Config config;
  auto retval = zephir::commands::optparse(argc, argv);
  if (retval == EXIT_HELP) {
    retval = 0;
  }

  if (retval != 0) {
    // TODO(klay): Throw exception. Args related?
  }

  if (!config_file.empty()) {
    retval = parse_yaml_config(&config, config_file);
    if (retval != EXIT_NO_CONFIG) {
      // TODO(klay): Throw exception. Config is broken?
    }
  }

  return config;
}
