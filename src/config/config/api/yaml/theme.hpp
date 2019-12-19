// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_THEME_HPP_
#define ZEPHIR_CONFIG_YAML_THEME_HPP_

#include <yaml-cpp/yaml.h>

#include "../ptr/theme.hpp"

namespace YAML {
template <>
struct convert<zephir::config::api::ThemePtr> {
  static Node encode(const zephir::config::api::ThemePtr &tptr);
  static bool decode(const Node &node, zephir::config::api::ThemePtr &tptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_THEME_HPP_
