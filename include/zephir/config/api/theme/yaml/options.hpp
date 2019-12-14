// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_THEME_YAML_OPTIONS_HPP_
#define ZEPHIR_CONFIG_API_THEME_YAML_OPTIONS_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/api/theme/ptr/options.hpp>

namespace ztheme = zephir::config::api::theme;

namespace YAML {
template <>
struct convert<ztheme::OptionsPtr> {
  static Node encode(const zephir::config::api::theme::OptionsPtr &optr);
  static bool decode(const Node &node, ztheme::OptionsPtr &optr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_API_THEME_YAML_OPTIONS_HPP_
