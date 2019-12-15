// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_THEME_HPP_
#define ZEPHIR_CONFIG_API_THEME_HPP_

#include <string>

#include <zephir/config/api/theme/options.hpp>
#include <zephir/config/api/yaml/theme.hpp>

namespace zephir::config::api {
class Theme {
 public:
  Theme();
  explicit Theme(std::string name, const theme::Options &options);

  friend YAML::Node
  YAML::convert<ThemePtr>::encode(const zephir::config::api::ThemePtr &tptr);
  friend bool
  YAML::convert<ThemePtr>::decode(const YAML::Node &node,
                                  zephir::config::api::ThemePtr &tptr);

  bool operator==(const Theme &rhs) const;
  Theme &operator=(const Theme &rhs);

 private:
  std::string name_;
  theme::Options options_;
};
}  // namespace zephir::config::api

#endif  // ZEPHIR_CONFIG_API_THEME_HPP_
