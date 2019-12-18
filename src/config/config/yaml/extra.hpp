// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_EXTRA_HPP_
#define ZEPHIR_CONFIG_YAML_EXTRA_HPP_

#include <yaml-cpp/yaml.h>

#include "../ptr/extra.hpp"

namespace YAML {
template <>
struct convert<zephir::config::ExtraPtr> {
  /**
   * @brief Encode Extra object to a Yaml Node.
   *
   * @param eptr The smart pointer to a Extra instance
   * @return Yaml Node
   */
  static Node encode(const zephir::config::ExtraPtr &eptr);

  /**
   * @brief Decode Yaml Node to a Extra object.
   *
   * @param node The Yaml Node
   * @param eptr The smart pointer to a Extra instance
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::ExtraPtr &eptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_EXTRA_HPP_
