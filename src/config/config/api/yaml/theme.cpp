// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config/api/yaml/theme.hpp"

#include "zephir/config/api/theme.hpp"

namespace ztheme = zephir::config::api::theme;

YAML::Node YAML::convert<zephir::config::api::ThemePtr>::encode(
    const zephir::config::api::ThemePtr &tptr) {
  Node node;

  node["name"] = tptr->name_;
  node["options"] = std::make_shared<ztheme::Options>(tptr->options_);

  return node;
}

bool YAML::convert<zephir::config::api::ThemePtr>::decode(
    const YAML::Node &node, zephir::config::api::ThemePtr &tptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["name"] && node["name"].IsScalar()) {
    tptr->name_ = node["name"].as<std::string>();
  }

  if (node["options"] && node["options"].IsMap()) {
    ztheme::OptionsPtr o = std::make_shared<ztheme::Options>();
    YAML::convert<ztheme::OptionsPtr>::decode(node["options"], o);
    tptr->options_ = *o.get();
  }

  return true;
}
