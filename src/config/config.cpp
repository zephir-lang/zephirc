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

namespace {
/**
 * @brief Populate project configuration.
 *
 * @param path Configuration file.
 * @return Shared pointer to the zephir::Config
 */
zephir::ConfigPtr PopulateConfig(const std::string &path) {
  auto config = std::make_shared<zephir::Config>();

  if (!zephir::filesystem::Exists(path)) {
    // Nothing to do if we unable to find config file at the disk.
    return config;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    YAML::Node node = YAML::LoadFile(path);
    YAML::convert<zephir::ConfigPtr>::decode(node, config);

    return config;
  } catch (YAML::ParserException &e) {
    throw std::runtime_error("Config file is broken");
  }
}
}  // namespace

zephir::Config::Config()
    : ns_(),
      name_(),
      description_(),
      author_("Zephir Team"),
      version_("0.0.1"),
      backend_("ZendEngine3"),
      verbose_(false),
      silent_(false),
      path_(".zephir"),
      changed_(false),
      requires_(),
      stubs_(),
      api_(),
      warnings_(),
      optimizations_(),
      extra_() {}

zephir::Config::~Config() { DumpToFile(); }

void zephir::Config::DumpToFile() {
  if (changed_ && !path_.empty() && !zephir::filesystem::Exists(path_)) {
    // TODO(klay):
    // 1. Convert container_ to yaml
    // 2. Write yaml to path_
  }
}

bool zephir::Config::IsChanged() { return changed_; }

// TODO(klay): Rename CreateFromArgv -> Factory
zephir::ConfigPtr
zephir::Config::CreateFromArgv(std::vector<std::string> &options,
                               const std::string &path) {
  auto config = PopulateConfig(path);

  if (options.size() == 1) {
    return config;
  }

  // TODO(klay): Process config, use argv

  return config;
}

bool zephir::Config::operator==(const zephir::Config &rhs) const {
  auto lhs_key = std::tie(ns_, name_, description_, author_, version_, backend_,
                          verbose_, silent_, requires_, stubs_, api_, warnings_,
                          optimizations_, extra_);
  auto rhs_key = std::tie(rhs.ns_, rhs.name_, rhs.description_, rhs.author_,
                          rhs.version_, rhs.backend_, rhs.verbose_, rhs.silent_,
                          rhs.requires_, rhs.stubs_, rhs.api_, rhs.warnings_,
                          rhs.optimizations_, rhs.extra_);

  return lhs_key == rhs_key;
}

zephir::Config &zephir::Config::operator=(const zephir::Config &rhs) = default;
