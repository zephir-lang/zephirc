// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_REQUIRES_HPP_
#define ZEPHIR_CONFIG_REQUIRES_HPP_

#include <string>
#include <vector>

#include <zephir/config/yaml/requires.hpp>

namespace zephir::config {
class Requires {
 public:
  Requires();
  explicit Requires(std::vector<std::string> extensions);

  /**
   * @brief Encode Requires object to the Yaml Node.
   *
   * @param rptr Requires smart pointer
   * @return Yaml Node
   */
  friend YAML::Node
  YAML::convert<RequiresPtr>::encode(const zephir::config::RequiresPtr &rptr);

  /**
   * @brief Decode Yaml Node to the Requires object.
   *
   * @param node Yaml Node
   * @param rptr Requires smart pointer
   * @return true on success, false otherwise
   */
  friend bool
  YAML::convert<RequiresPtr>::decode(const YAML::Node &node,
                                     zephir::config::RequiresPtr &rptr);

  bool operator==(const Requires &rhs) const;
  Requires &operator=(const Requires &rhs);

 private:
  std::vector<std::string> extensions_;
};
}  // namespace zephir::config

#endif  // ZEPHIR_CONFIG_REQUIRES_HPP_
