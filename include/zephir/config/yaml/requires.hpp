// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_REQUIRES_HPP_
#define ZEPHIR_CONFIG_YAML_REQUIRES_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/ptr/requires.hpp>

namespace YAML {
template <>
struct convert<zephir::config::RequiresPtr> {
  static Node encode(const zephir::config::RequiresPtr &rptr);
  static bool decode(const Node &node, zephir::config::RequiresPtr &rptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_REQUIRES_HPP_
