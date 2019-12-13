// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config/yaml/warnings.hpp"

#include "zephir/config/warnings.hpp"

YAML::Node YAML::convert<zephir::config::WarningsPtr>::encode(
    const zephir::config::WarningsPtr &wptr) {
  Node node;

  for (auto const &[key, val] : wptr->container_) {
    node[key] = val;
  }

  return node;
}

bool YAML::convert<zephir::config::WarningsPtr>::decode(
    const YAML::Node &node, zephir::config::WarningsPtr &wptr) {
  if (!node.IsMap()) {
    return false;
  }

  for (YAML::const_iterator n = node.begin(); n != node.end(); ++n) {
    auto it = wptr->container_.find(n->first.as<std::string>());
    if (it != wptr->container_.end()) {
      it->second = n->second.as<bool>();
    }
  }

  return true;
}
