// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <zephir/config/api/theme/options.hpp>

namespace ztheme = zephir::config::api::theme;

YAML::Node
YAML::convert<ztheme::OptionsPtr>::encode(const ztheme::OptionsPtr &wptr) {
  Node node;

  for (auto const &[key, val] : wptr->container_) {
    node[key] = val;
  }

  return node;
}

bool YAML::convert<ztheme::OptionsPtr>::decode(const YAML::Node &node,
                                               ztheme::OptionsPtr &wptr) {
  if (!node.IsMap()) {
    return false;
  }

  for (YAML::const_iterator n = node.begin(); n != node.end(); ++n) {
    auto it = wptr->container_.find(n->first.as<std::string>());
    if (it != wptr->container_.end()) {
      if (n->second.IsScalar() || n->second.IsNull()) {
        it->second = n->second.as<std::string>();
      }
    }
  }

  return true;
}
