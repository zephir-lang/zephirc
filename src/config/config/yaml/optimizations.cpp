// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config/yaml/optimizations.hpp"

#include "zephir/config/optimizations.hpp"

YAML::Node YAML::convert<zephir::config::OptimizationsPtr>::encode(
    const zephir::config::OptimizationsPtr &optr) {
  Node node;

  for (auto const &[key, val] : optr->container_) {
    node[key] = val;
  }

  return node;
}

bool YAML::convert<zephir::config::OptimizationsPtr>::decode(
    const YAML::Node &node, zephir::config::OptimizationsPtr &optr) {
  if (!node.IsMap()) {
    return false;
  }

  for (YAML::const_iterator n = node.begin(); n != node.end(); ++n) {
    auto it = optr->container_.find(n->first.as<std::string>());
    if (it != optr->container_.end() && n->second.IsScalar()) {
      it->second = n->second.as<bool>();
    }
  }

  return true;
}
