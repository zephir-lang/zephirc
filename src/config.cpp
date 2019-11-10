// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <yaml-cpp/yaml.h>
#include <filesystem>

#include "zephir/main.hpp"
#include "zephir/config.hpp"
#include "commands/commands.hpp"

namespace {
int parse_yaml_config(core::Config *config, const std::string &config_file) {
  if (!std::filesystem::exists(config_file)) {
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

int core::load_config(core::Config *config, int argc, char **argv,
                      std::string config_file) {
  auto retval = commands::optparse(argc, argv);
  if (retval == EXIT_HELP) {
    retval = 0;
  }

  if (retval != 0) {
    return retval;
  }

  if (!config_file.empty()) {
    retval = parse_yaml_config(config, config_file);
    if (retval == EXIT_NO_CONFIG) {
      retval = 0;
    }
  }

  return retval;
}
