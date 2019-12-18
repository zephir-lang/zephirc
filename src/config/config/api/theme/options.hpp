// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_THEME_OPTIONS_HPP_
#define ZEPHIR_CONFIG_API_THEME_OPTIONS_HPP_

#include <string>

#include "yaml/options.hpp"

namespace ztheme = zephir::config::api::theme;

namespace zephir::config::api::theme {
class Options {
 public:
  Options();
  explicit Options(std::map<std::string, std::string> container);

  friend YAML::Node
  YAML::convert<OptionsPtr>::encode(const ztheme::OptionsPtr &optr);
  friend bool YAML::convert<OptionsPtr>::decode(const YAML::Node &node,
                                                ztheme::OptionsPtr &optr);

  bool operator==(const Options &rhs) const;
  Options &operator=(const Options &rhs);

 private:
  std::map<std::string, std::string> container_;
};
}  // namespace zephir::config::api::theme
#endif  // ZEPHIR_CONFIG_API_THEME_OPTIONS_HPP_
