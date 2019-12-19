// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_YAML_CONFIG_HPP_
#define ZEPHIR_YAML_CONFIG_HPP_

#include <yaml-cpp/yaml.h>

#include "../ptr/config.hpp"

namespace YAML {
template <>
struct convert<zephir::ConfigPtr> {
  /**
   * @brief Encode Config object to a Yaml Node.
   *
   * @param cptr The smart pointer to a Config instance
   * @return Yaml Node
   */
  static Node encode(const zephir::ConfigPtr &cptr);

  /**
   * @brief Decode Yaml Node to a Config object.
   *
   * @param node The Yaml Node
   * @param cptr The smart pointer to a Config instance
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::ConfigPtr &cptr);
};
}  // namespace YAML

#endif  // ZEPHIR_YAML_CONFIG_HPP_
