// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_EXTRA_HPP_
#define ZEPHIR_CONFIG_EXTRA_HPP_

#include <string>

#include <zephir/config/yaml/extra.hpp>

namespace zephir::config {
class Extra {
 public:
  Extra();
  explicit Extra(std::string indent, bool exportc);

  /**
   * @brief Encode Extra object to a Yaml Node.
   *
   * @param eptr The smart pointer to a Extra instance
   * @return Yaml Node
   */
  friend YAML::Node
  YAML::convert<ExtraPtr>::encode(const zephir::config::ExtraPtr &eptr);

  /**
   * @brief Decode Yaml Node to a Extra object.
   *
   * @param node The Yaml Node
   * @param eptr The smart pointer to a Extra instance
   * @return true on success, false otherwise
   */
  friend bool YAML::convert<ExtraPtr>::decode(const YAML::Node &node,
                                              zephir::config::ExtraPtr &eptr);

  bool operator==(const Extra &rhs) const;
  Extra &operator=(const Extra &rhs);

 private:
  std::string indent_;
  bool exportc_;
};
}  // namespace zephir::config
#endif  // ZEPHIR_CONFIG_EXTRA_HPP_
