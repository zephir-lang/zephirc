// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "../requires.hpp"

YAML::Node YAML::convert<zephir::config::RequiresPtr>::encode(
    const zephir::config::RequiresPtr &rptr) {
  Node node;
  node["extensions"] = rptr->extensions_;

  return node;
}

bool YAML::convert<zephir::config::RequiresPtr>::decode(
    const YAML::Node &node, zephir::config::RequiresPtr &rptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["extensions"] && node["extensions"].IsSequence()) {
    rptr->extensions_ = node["extensions"].as<std::vector<std::string>>();
  }

  return true;
}
