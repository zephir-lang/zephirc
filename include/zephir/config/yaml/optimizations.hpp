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
   * @brief Encode Optimizations object to a Yaml Node.
   *
   * @param optr The smart pointer to a Optimizations instance
   * @return Yaml Node
   */
  static Node encode(const zephir::config::OptimizationsPtr &optr);

  /**
   * @brief Decode Yaml Node to a Optimizations object.
   *
   * @param node The Yaml Node
   * @param optr The smart pointer to a Optimizations instance
   * @return true on success, false otherwise
   */
  static bool decode(const Node &node, zephir::config::OptimizationsPtr &optr);
};
}  // namespace YAML

#endif  // ZEPHIR_CONFIG_YAML_OPTIMIZATIONS_HPP_
