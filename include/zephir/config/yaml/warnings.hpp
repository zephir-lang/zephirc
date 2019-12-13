// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_WARNINGS_HPP_
#define ZEPHIR_CONFIG_YAML_WARNINGS_HPP_

#include <yaml-cpp/yaml.h>

#include "zephir/config/ptr/warnings.hpp"

namespace YAML {
template <>
struct convert<zephir::config::WarningsPtr> {
  static Node encode(const zephir::config::WarningsPtr &wptr);
  static bool decode(const Node &node, zephir::config::WarningsPtr &wptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_WARNINGS_HPP_
