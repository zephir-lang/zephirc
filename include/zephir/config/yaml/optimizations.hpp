// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_YAML_OPTIMIZATIONS_HPP_
#define ZEPHIR_CONFIG_YAML_OPTIMIZATIONS_HPP_

#include <yaml-cpp/yaml.h>

#include <zephir/config/ptr/optimizations.hpp>

namespace YAML {
template <>
struct convert<zephir::config::OptimizationsPtr> {
  /**
   * @brief Encode Optimizations object to the Yaml Node.
   *
   * @param optr Optimizations smart pointer
   * @return Yaml Node
   */
  static Node encode(const zephir::config::OptimizationsPtr &optr);

  /**
   * @brief Decode Yaml Node to the Optimizations object.
   *
   * @param node Yaml Node
   * @param optr Optimizations smart pointer
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::OptimizationsPtr &optr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_OPTIMIZATIONS_HPP_
