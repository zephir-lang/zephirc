// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <zephir/config/stubs.hpp>

YAML::Node YAML::convert<zephir::config::StubsPtr>::encode(
    const zephir::config::StubsPtr &sptr) {
  Node node;
  node["path"] = sptr->path_;
  node["stubs-run-after-generate"] = sptr->regenerate_;
  node["banner"] = sptr->banner_;

  return node;
}

bool YAML::convert<zephir::config::StubsPtr>::decode(
    const YAML::Node &node, zephir::config::StubsPtr &sptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["path"] && node["path"].IsScalar()) {
    sptr->path_ = node["path"].as<std::string>();
  }

  if (node["stubs-run-after-generate"] &&
      node["stubs-run-after-generate"].IsScalar()) {
    sptr->regenerate_ = node["stubs-run-after-generate"].as<bool>();
  }

  if (node["banner"] && node["banner"].IsScalar()) {
    sptr->banner_ = node["banner"].as<std::string>();
  }

  return true;
}
