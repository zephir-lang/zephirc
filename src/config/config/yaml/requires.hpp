// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_REQUIRES_HPP_
#define ZEPHIR_CONFIG_YAML_REQUIRES_HPP_

#include <yaml-cpp/yaml.h>

#include "../ptr/requires.hpp"

namespace YAML {
template <>
struct convert<zephir::config::RequiresPtr> {
  /**
   * @brief Encode Requires object to a Yaml Node.
   *
   * @param rptr The smart pointer to a Requires instance
   * @return Yaml Node
   */
  static Node encode(const zephir::config::RequiresPtr &rptr);

  /**
   * @brief Decode Yaml Node to a Requires object.
   *
   * @param node The Yaml Node
   * @param rptr The smart pointer to a Requires instance
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::RequiresPtr &rptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_REQUIRES_HPP_
