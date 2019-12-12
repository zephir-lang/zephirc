//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_EXTRA_HPP_
#define ZEPHIR_CONFIG_EXTRA_HPP_

#include "zephir/config/yaml/extra.hpp"

namespace zephir {
namespace config {
class Extra {
 public:
  Extra();
  Extra(std::string indent, bool exportc);

  friend YAML::Node
  YAML::convert<ExtraPtr>::encode(const zephir::config::ExtraPtr &eptr);
  friend bool YAML::convert<ExtraPtr>::decode(const YAML::Node &node,
                                              zephir::config::ExtraPtr &eptr);

  bool operator==(const Extra &rhs) const;
  Extra &operator=(const Extra &rhs);

 private:
  std::string indent_;
  bool exportc_;
};
}  // namespace config
}  // namespace zephir
#endif  // ZEPHIR_CONFIG_EXTRA_HPP_