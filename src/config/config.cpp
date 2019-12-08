// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config.hpp"

#include <yaml-cpp/yaml.h>

#include "commands/commands.hpp"
#include "zephir/filesystem.hpp"
#include "zephir/main.hpp"

zephir::Config::Config(const std::string &file) {
  if (!file.empty()) {
    int retval = Populate(file);
    switch (retval) {
      case EXIT_BAD_CONFIG:
        throw std::runtime_error("Config file is broken");
      case EXIT_NO_CONFIG:
        // Nothing to do if we unable to find config file at the disk.
        break;
      default:
        break;
    }
  }
}

int zephir::Config::Populate(const std::string &file) {
  if (!zephir::filesystem::Exists(file)) {
    // Do nothing.
    return EXIT_NO_CONFIG;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    YAML::Node loaded_config = YAML::LoadFile(file);
  } catch (YAML::ParserException &e) {
    return EXIT_BAD_CONFIG;
  }

  // TODO(klay): Implement me.
  return 0;
}

bool zephir::Config::IsChanged() { return changed; }

zephir::Config zephir::Config::CreateFromArgv(std::vector<std::string> &options,
                                              const std::string &file) {
  zephir::Config config(file);
  if (options.size() == 1) {
    return config;
  }

  // TODO(klay): Process config, use argv

  return config;
}
