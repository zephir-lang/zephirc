// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_EXTRA_HPP_
#define ZEPHIR_CONFIG_YAML_EXTRA_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/ptr/extra.hpp>

namespace YAML {
template <>
struct convert<zephir::config::ExtraPtr> {
  /**
   * @brief Encode Extra object to the Yaml Node.
   *
   * @param eptr Extra smart pointer
   * @return Yaml Node
   */
  static Node encode(const zephir::config::ExtraPtr &eptr);

  /**
   * @brief Decode Yaml Node to the Extra object.
   *
   * @param node Yaml Node
   * @param eptr Extra smart pointer
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::ExtraPtr &eptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_EXTRA_HPP_
