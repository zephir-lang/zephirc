// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <zephir/config/api.hpp>

YAML::Node YAML::convert<zephir::config::ApiPtr>::encode(
    const zephir::config::ApiPtr &aptr) {
  Node node;

  node["path"] = aptr->path_;
  node["theme"] = std::make_shared<zephir::config::api::Theme>(aptr->theme_);

  return node;
}

bool YAML::convert<zephir::config::ApiPtr>::decode(
    const YAML::Node &node, zephir::config::ApiPtr &aptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["path"] && node["path"].IsScalar()) {
    aptr->path_ = node["path"].as<std::string>();
  }

  if (node["theme"] && node["theme"].IsMap()) {
    auto t = std::make_shared<zephir::config::api::Theme>();
    YAML::convert<zephir::config::api::ThemePtr>::decode(node["theme"], t);
    aptr->theme_ = *t;
  }

  return true;
}
