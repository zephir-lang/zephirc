// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config.hpp"

#include <filesystem>
#include <fstream>

#include "../filesystem/filesystem.hpp"

namespace fs = std::filesystem;

zephir::Config::Config()
    : ns_(),
      name_(),
      description_(),
      author_("Zephir Team"),
      version_("0.0.1"),
      backend_("ZendEngine3"),
      verbose_(false),
      silent_(false),
      path_(""),
      changed_(false),
      requires_(),
      stubs_(),
      api_(),
      warnings_(),
      optimizations_(),
      extra_() {}

zephir::Config::~Config() { DumpToFile(); }

zephir::ConfigPtr zephir::Config::Load(const std::string &path) {
  auto config = std::make_shared<zephir::Config>();
  config->path_ = path;

  if (!zephir::filesystem::Exists(config->path_)) {
    // Nothing to do if we unable to find config file at the disk.
    return config;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    YAML::Node node = YAML::LoadFile(config->path_);
    YAML::convert<zephir::ConfigPtr>::decode(node, config);

    return config;
  } catch (YAML::ParserException &e) {
    throw std::runtime_error("Config file is broken");
  }
}

void zephir::Config::DumpToFile() {
  if (changed_ && !path_.empty() && !zephir::filesystem::Exists(path_)) {
    auto yaml = YAML::convert<zephir::ConfigPtr>::encode(shared_from_this());

    fs::path path(path_);
    std::ofstream ofs(path);

    ofs << yaml;
    ofs.close();
  }
}

bool zephir::Config::IsChanged() { return changed_; }

zephir::ConfigPtr zephir::Config::Factory(std::vector<std::string> &options,
                                          const std::string &path) {
  auto config = zephir::Config::Load(path);

  if (!options.empty()) {
    // TODO(klay): Process config, use argv
  }

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
