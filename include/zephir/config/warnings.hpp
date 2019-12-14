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

#include <zephir/config/yaml/warnings.hpp>

namespace zephir::config {
class Warnings {
 public:
  Warnings();
  explicit Warnings(std::map<std::string, bool> container);

  friend YAML::Node
  YAML::convert<WarningsPtr>::encode(const zephir::config::WarningsPtr &wptr);
  friend bool
  YAML::convert<WarningsPtr>::decode(const YAML::Node &node,
                                     zephir::config::WarningsPtr &wptr);

  bool operator==(const Warnings &rhs) const;
  Warnings &operator=(const Warnings &rhs);

 private:
  std::map<std::string, bool> container_;
};
}  // namespace zephir::config
#endif  // ZEPHIR_CONFIG_WARNINGS_HPP_
