// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_STUBS_HPP_
#define ZEPHIR_CONFIG_YAML_STUBS_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/ptr/stubs.hpp>

namespace YAML {
template <>
struct convert<zephir::config::StubsPtr> {
  /**
   * @brief Encode Stubs object to the Yaml Node.
   *
   * @param sptr Stubs smart pointer
   * @return Yaml Node
   */
  static Node encode(const zephir::config::StubsPtr &sptr);

  /**
   * @brief Decode Yaml Node to the Warnings object.
   *
   * @param node Yaml Node
   * @param wptr Warnings smart pointer
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::StubsPtr &sptr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_STUBS_HPP_
