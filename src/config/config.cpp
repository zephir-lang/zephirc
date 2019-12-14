// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <yaml-cpp/yaml.h>

#include <memory>

#include <zephir/commands.hpp>
#include <zephir/config.hpp>
#include <zephir/filesystem.hpp>
#include <zephir/main.hpp>

zephir::Config::Config(std::string path)
    : path_(std::move(path)), changed_(false) {
  if (!path_.empty()) {
    switch (Populate(path_)) {
      case EXIT_BAD_CONFIG:
        throw std::runtime_error("Config file is broken");
      // Nothing to do if we unable to find config file at the disk.
      case EXIT_NO_CONFIG:
      default:
        break;
    }
  }
}

zephir::Config::~Config() { DumpToFile(); }

void zephir::Config::DumpToFile() {
  if (changed_ && !path_.empty() && !zephir::filesystem::Exists(path_)) {
    // TODO(klay):
    // 1. Convert container_ to yaml
    // 2. Write yaml to path_
  }
}

int zephir::Config::Populate(const std::string &path) {
  if (!zephir::filesystem::Exists(path)) {
    // Do nothing.
    return EXIT_NO_CONFIG;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    YAML::Node loaded_config = YAML::LoadFile(path);
  } catch (YAML::ParserException &e) {
    return EXIT_BAD_CONFIG;
  }

  // TODO(klay): Implement me.
  return 0;
}

bool zephir::Config::IsChanged() { return changed_; }

std::shared_ptr<zephir::Config>
zephir::Config::CreateFromArgv(std::vector<std::string> &options,
                               const std::string &path) {
  auto config = std::make_shared<zephir::Config>(path);

  if (options.size() == 1) {
    return config;
  }

  // TODO(klay): Process config, use argv

  return config;
}
