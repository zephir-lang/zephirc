// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_WARNINGS_HPP_
#define ZEPHIR_CONFIG_WARNINGS_HPP_

#include <map>
#include <string>

#include "yaml/warnings.hpp"

namespace zephir::config {
class Warnings {
 public:
  Warnings();
  explicit Warnings(std::map<std::string, bool> container);

  /**
   * @brief Encode Warnings object to a Yaml Node.
   *
   * @param wptr The smart pointer to a Warnings instance
   * @return Yaml Node
   */
  friend YAML::Node
  YAML::convert<WarningsPtr>::encode(const zephir::config::WarningsPtr &wptr);

  /**
   * @brief Decode Yaml Node to a Warnings object.
   *
   * @param node The Yaml Node
   * @param wptr The smart pointer to a Warnings instance
   * @return true on success, false otherwise
   */
  friend bool
  YAML::convert<WarningsPtr>::decode(const YAML::Node &node,
                                     zephir::config::WarningsPtr &wptr);

  bool operator==(const Warnings &rhs) const;
  Warnings &operator=(const Warnings &rhs);

  /**
   * @brief Sets a warning flag value.
   *
   * @param key The flag.
   * @param value The value.
   * @return Return boolean true if flag is exists, boolean false otherwise.
   */
  bool update(const std::string &key, const bool &value);

  std::map<std::string, bool> container;
};
}  // namespace zephir::config
#endif  // ZEPHIR_CONFIG_WARNINGS_HPP_
